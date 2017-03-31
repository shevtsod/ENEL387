/*
* FILENAME: prog_snake.c
*
*	DESCRIPTION:
*		Game 1 - Snake state
*
*	AUTHOR: Daniel Shevtsov, SID: 200351253 
*/

#include "prog_snake.h"

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//Private function prototypes
static void playGame(void);

//Game data
#define NUM_ROWS				4
#define NUM_COLS				16

#define GRID_EMPTY			' '
#define GRID_PLAYER			'O'
#define GRID_TOKEN			'*'

#define NEEDED_TOKENS 	4

#define DIRECTION_RIGHT 0
#define DIRECTION_DOWN  1
#define DIRECTION_LEFT  2
#define DIRECTION_UP  	3

static char grid[NUM_ROWS][NUM_COLS];

//Player data
static int currentX;
static int currentY;
static int currentTokens;
static bool alive;
static int currentDirection;

//Token data
static int tokenX;
static int tokenY;
static bool existsToken;


/*
 Allows the game's data to be reset to its original values when re-entering the game
*/
void resetSnake(void) {
	currentX = 0;
	currentY = 0;
	currentTokens = 0;
	alive = true;
	currentDirection = DIRECTION_RIGHT;
	
	tokenX = -1;
	tokenY = -1;
	existsToken = false;
	
	//Reset outputs
	setLED1(0);
	setLED2(0);
	setLED3(0);
	setLED4(0);
	setPWMEnabled(0);
	
	memset(grid, GRID_EMPTY, sizeof grid);
	grid[currentY][currentX] = GRID_PLAYER;
}

void stateGameSnake(void) {
	//Convert 2D array to 4 strings to output	
	char ln1[NUM_COLS + 1];
	char ln2[NUM_COLS + 1];
	char ln3[NUM_COLS + 1];
	char ln4[NUM_COLS + 1];

	memcpy(ln1, grid[0], sizeof grid[0]);
	memcpy(ln2, grid[1], sizeof grid[0]);
	memcpy(ln3, grid[2], sizeof grid[0]);
	memcpy(ln4, grid[3], sizeof grid[0]);

	ln1[NUM_COLS] = '\0';
	ln2[NUM_COLS] = '\0';
	ln3[NUM_COLS] = '\0';
	ln4[NUM_COLS] = '\0';
	
	if(alive) {
		//Play game if still alive
		playGame();
		
		//Output grid to screen
		println1(ln1);
		println2(ln2);
		println3(ln3);
		println4(ln4);
		
		//Show current number of tokens in the LEDs
		switch(currentTokens) {
			case 4: setLED4(1);
			case 3: setLED3(1);
			case 2: setLED2(1);
			case 1: setLED1(1);
		}
		
		delayMS(150);
		
	} 
	else {
		//If not alive, print a menu of post-game options
		if(getA()) {
			resetSnake();
		}
		
		if(currentTokens < NEEDED_TOKENS)
			println1("   GAME  OVER");
		else
			println1("   YOU   WIN!");
		println2("Press MENU to");
		println3("exit or A to");
		println4("play again");
		
		setPWMEnabled(1);
	}
}

/*
This function handles game logic while player is still alive
*/
void playGame(void) {
	//Check number of tokens. If needed amount was collected, then the game is over
	if(currentTokens == NEEDED_TOKENS) {
			alive = false;
			return;
		}
	
	//If token does not exist, create a new one in a random grid location
	if(!existsToken) {
		do {
			//In range 0 to 16
			tokenX = rand() % (NUM_COLS);
			//In range 0 to 4
			tokenY = rand() % (NUM_ROWS);
		} 	while(tokenX == currentX && tokenY == currentY);
		
		grid[tokenY][tokenX] = GRID_TOKEN;
		
		existsToken = true;
	}
	
	//Remove the player from the previous grid location
	grid[currentY][currentX] = GRID_EMPTY;
	
	//Handle user input, if no user input proceed in previous direction
	if(getPosX()) {
		currentDirection = DIRECTION_RIGHT;
	} else if (getNegX()) {
		currentDirection = DIRECTION_LEFT;
	} else if (getPosY()) {	
		currentDirection = DIRECTION_UP;
	} else if (getNegY()) {
		currentDirection = DIRECTION_DOWN;
	}
		
	//Move based on currentDirection
	if(currentDirection == DIRECTION_RIGHT) {
		currentX++;
	} else if (currentDirection == DIRECTION_LEFT) {
		currentX--;
	} else if (currentDirection == DIRECTION_UP) {
		currentY--;
	} else if (currentDirection == DIRECTION_DOWN) {
		currentY++;
	}
	
	//If out of bounds, kill the player
	if(currentX < 0 || currentX >= NUM_COLS
		|| currentY < 0 || currentY >= NUM_ROWS) {
		alive = false;
		return;
	}
	
	//Place the player on the grid, 
	//but check if there is a token here first
	if(currentX == tokenX && currentY == tokenY) {
		currentTokens++;
		
		//Play sound cue for collecitng a token
		setPWMEnabled(1);
		delayMS(100);
		setPWMEnabled(0);
		
		existsToken = false;
	}
	
	//Update player location on grid
	grid[currentY][currentX] = GRID_PLAYER;
}
