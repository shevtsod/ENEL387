/*
* FILENAME: prog_connect4.c
*
*	DESCRIPTION:
*		Game 3 - Connect Four state
*
*	AUTHOR: Daniel Shevtsov, SID: 200351253 
*/

#include "prog_connect4.h"

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

//Private function prototypes
static void selectPlayerIcon(void);
static void playPlayer(void);
static void playAI(void);
static void checkBoard(void);

//Game data
#define NUM_ROWS								4

#define SYMBOL_A								'A'
#define SYMBOL_B								'B'
#define SYMBOL_EMPTY						' '
#define SYMBOL_CURSOR						'_'
#define SYMBOL_WALL							'.'

#define GAMESTATE_ICON_SELECT 	0
#define GAMESTATE_PLAY					1
#define GAMESTATE_OVER 					2

#define PLAYER									0
#define AI											1

static char board[NUM_ROWS][NUM_ROWS];
static int gameState;
static int playerIcon;
static int aiIcon;
static int currentTurn;
static int currentIcons;
static int winner;

static int currentX;

//Convert 2D array to 4 strings to output
static char ln1[17];
static char ln2[17];
static char ln3[17];
static char ln4[17];


/*
 Allows the game's data to be reset to its original values when re-entering the game
*/
void resetConnect4(void) {
	memset(board, SYMBOL_EMPTY, sizeof board);
	gameState = GAMESTATE_ICON_SELECT;
	currentIcons = 0;
	
	currentX = 0;
	
	//Reset outputs
	println1("");
	println2("");
	println3("");
	println4("");
	setLED1(0);
	setLED2(0);
	setLED3(0);
	setLED4(0);
	setPWMEnabled(0);
}

void stateGameConnect4(void) {
	
	if(gameState == GAMESTATE_ICON_SELECT) {
		println1("  SELECT ICON:  ");
		println2("PRESS A FOR A");
		println3("PRESS B FOR B");
		
		selectPlayerIcon();
		
	} 
	else if (gameState == GAMESTATE_PLAY) {
		//Convert 2D char array to 4 strings
		char temp[8 + NUM_ROWS];
		
		memset(temp, SYMBOL_WALL, sizeof temp);
		temp[6] = '\0';
		memcpy(ln1, board[0], NUM_ROWS);
		ln1[NUM_ROWS] = '\0';
		strcat(temp, ln1);
		strcpy(ln1, temp);
		memset(temp, SYMBOL_WALL, sizeof temp);
		temp[5] = '\0';
		strcat(ln1, temp);
		if(currentTurn == PLAYER)
			strcat(ln1, "P");
		else if(currentTurn == AI)
			strcat(ln1, "A");
		
		memset(temp, SYMBOL_WALL, sizeof temp);
		temp[6] = '\0';
		memcpy(ln2, board[1], NUM_ROWS);
		ln2[NUM_ROWS] = '\0';
		strcat(temp, ln2);
		strcpy(ln2, temp);
		memset(temp, SYMBOL_WALL, sizeof temp);
		temp[6] = '\0';
		strcat(ln2, temp);

		memset(temp, SYMBOL_WALL, sizeof temp);
		temp[6] = '\0';
		memcpy(ln3, board[2], NUM_ROWS);
		ln3[NUM_ROWS] = '\0';
		strcat(temp, ln3);
		strcpy(ln3, temp);
		memset(temp, SYMBOL_WALL, sizeof temp);
		temp[6] = '\0';
		strcat(ln3, temp);

		memset(temp, SYMBOL_WALL, sizeof temp);
		temp[6] = '\0';
		memcpy(ln4, board[3], NUM_ROWS);
		ln4[NUM_ROWS] = '\0';
		strcat(temp, ln4);
		strcpy(ln4, temp);
		memset(temp, SYMBOL_WALL, sizeof temp);
		temp[6] = '\0';
		strcat(ln4, temp);
		
		println1(ln1);
		println2(ln2);
		println3(ln3);
		println4(ln4);
		
		checkBoard();
		
		if(gameState != GAMESTATE_PLAY)
			return;
		
		if(currentTurn == PLAYER) {
			playPlayer();
		}
		else {
			playAI();
		}
		
	} 
	else if (gameState == GAMESTATE_OVER) {
		//Show end game screen for 1 second and beep buzzer
		//to indicate game over
		setPWMEnabled(1);
		
		if(winner == PLAYER) {
			setLED1(1);
			setLED2(2);
			setLED3(3);
			setLED4(4);
		}
		
		if(winner == PLAYER)
			println1("   YOU   WIN!");
		else if(winner == AI)
			println1("    AI  WINS");
		else
			println1("      DRAW");
		
		println2("Press MENU to");
		println3("exit or A to");
		println4("play again");
		
		if(getA()) {
			resetConnect4();
		}
	}
}

/*
* This function handles logic for selecting the player's symbol and turn order
*/
static void selectPlayerIcon(void) {
	if(getA()) {
		playerIcon = SYMBOL_A;
		aiIcon = SYMBOL_B;
		currentTurn = PLAYER;
		
		gameState = GAMESTATE_PLAY;
	}
	else if(getB()) {
		playerIcon = SYMBOL_B;
		aiIcon = SYMBOL_A;
		currentTurn = AI;
		
		gameState = GAMESTATE_PLAY;
	}
}

/*
* This function handles game logic for player's turn
*/
static void playPlayer(void) {
	int i;
	bool iconPlaced = false;
	
	//Remove preview cursor on currently selected cell
	if(board[0][currentX] == SYMBOL_CURSOR)
		board[0][currentX] = SYMBOL_EMPTY;
	
	//Navigate to desired cell
	if(getPosX()) {
		if(currentX < NUM_ROWS - 1)
			currentX++;
	} else if(getNegX()) {
		if(currentX > 0)
			currentX--;
	}
		
	//Place preview cursor on currently selected cell
	if(board[0][currentX] != aiIcon && board[0][currentX] != playerIcon)
		board[0][currentX] = SYMBOL_CURSOR;
	
	//If A is pressed, place the icon in the lowest empty cell with that X coordinate
	if(getA()) {
		
		for(i = NUM_ROWS - 1; i >= 0; i--) {
			if(board[i][currentX] != aiIcon && board[i][currentX] != playerIcon) {
				board[i][currentX] = playerIcon;
				iconPlaced = true;
				break;
			}
		}
		
	}
	
	//Proceed to AI's turn
	if(iconPlaced) {
		currentIcons++;
		currentTurn = AI;
	}
}

/*
* This function handles game logic for AI's turn
*/
static void playAI(void) {
	int iconX, i;
	bool iconPlaced = false;
	
	//Get a random empty cell
	do {
		iconX = rand() % NUM_ROWS;
		
		for(i = NUM_ROWS - 1; i >= 0; i--) {
			//Place the AI's icon in the lowest available empty cell
			if(board[i][iconX] != aiIcon && board[i][iconX] != playerIcon) {
				board[i][iconX] = aiIcon;
				iconPlaced = true;
				break;
			}
		}
		
	} while(!iconPlaced);
	
	//Proceed to player's turn
	currentIcons++;
	currentTurn = PLAYER;
}

/*
* This function checks if a player got 3 in a row, column, or diagonal
* If so, it sets GAMESTATE to GAMESTATE_OVER and stores the winner in winner
*/
static void checkBoard(void) {
	int i, j;
	char checkSymbol;
	bool isWinner = false;
	
	//Check for any full row
	for(j = 0; j < NUM_ROWS; j++) {
		
		if(isWinner)
			break;
		
		//Compare symbol of first element to rest of elements
		checkSymbol = board[j][i];
		
		if(checkSymbol != aiIcon && checkSymbol != playerIcon)
			continue;
		
		for(i = 0; i < NUM_ROWS; i++) {
			if(board[j][i] != checkSymbol)
				break;
			if(i == NUM_ROWS - 1 && board[j][i] == checkSymbol)
				isWinner = true;
		}
		
	}
	
	//Check for any full column
	if(!isWinner) {
		for(j = 0; j < NUM_ROWS; j++) {
			
			if(isWinner)
				break;
		
			//Compare symbol of first element to rest of elements
			checkSymbol = board[i][j];
		
			if(checkSymbol != aiIcon && checkSymbol != playerIcon)
				continue;
		
			for(i = 0; i < NUM_ROWS; i++) {
				if(board[i][j] != checkSymbol)
					break;
				if(i == NUM_ROWS - 1 && board[i][j] == checkSymbol)
					isWinner = true;
			}
			
		}
	}
	
	//Check for forward diagonal
	if(!isWinner && (board[0][0] == aiIcon || board[0][0] == playerIcon)) {
		
		checkSymbol = board[0][0];
		
		for(i = 0; i < NUM_ROWS; i++) {
			if(board[i][i] != checkSymbol)
					break;
			if(i == NUM_ROWS - 1 && board[i][i] == checkSymbol)
				isWinner = true;
		}
	}
	
	//Check for backwards diagonal
	if(!isWinner && 
		(board[0][NUM_ROWS - 1] == aiIcon || 
		 board[0][NUM_ROWS - 1] == playerIcon)) {
		
		checkSymbol = board[0][NUM_ROWS - 1];
		
		j = 0;
			 
		for(i = NUM_ROWS - 1; i >= 0; i--) {			
			
			if(board[j][i] != checkSymbol)
					break;
			if(i == 0 && board[j][i] == checkSymbol)
				isWinner = true;
			
			j++;
		}
		
	}
	
	if(isWinner) {
		delayMS(1000);
	  gameState = GAMESTATE_OVER;
		if(checkSymbol == playerIcon)
			winner = PLAYER;
		else
			winner = AI;
		return;
	}
	
	//Check for 16 icons on board, decide on a draw
	if(currentIcons >= (NUM_ROWS * NUM_ROWS)) {
		delayMS(1000);
	  gameState = GAMESTATE_OVER;
		winner = -1;
	}
}
