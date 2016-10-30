#include "mainmenu.h"
#include "utilities.h"
#include <stdio.h>

void MainMenu_showSplashScreen() {
	clearScreen();
	printf("\n\n\n     <Team name> presents\n");
	delay(1.5);
	clearScreen();
	printf("\n\n\n     BRIGHTSOULS\n");
	delay(2.5);
}

void MainMenu_show(bool isGameRunning) {
	clearScreen();
	printf("\nShow main menu here, Ctrl+C to exit\n");
	delay(0.5);
}

// void MainMenu_processInput(GameState *gameState, bool *isGameRunning, bool *exitGame) {

//}
