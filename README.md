![Logo](http://i.imgur.com/5FoE0X3.png)
![Collage](http://i.imgur.com/FH6NWTA.jpg)
# ENEL 387 Project
Project for Electronics Engineering 387 - Microcomputer Systems Design

## Overview
This project implements a device capable of running multiple basic video games. At the core of the device is the STM32F100RB micro-controller, and the device comes with a basic controller with an analog stick, two buttons, a menu button, and a buzzer for audio cues. Games run on a 4x16 text display, with games also making use of four LEDs to display the game status to the player. When the system starts, the user is greeted with a menu to pick between available games, and at any point during a game, the user may choose to return to the menu and select a different game to play.

See `doc/` directory for additional documentation including Functional Specification, Final Report, and vendor datasheets.

## Compilation
Compiled using `Keil uVision5` and the `STM32F100RB` microcontroller.
