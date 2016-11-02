#include "boolean.h"
#include "gamestate.h"
#include "mainmenu.h"
#include "stringutils.h"
// #include "renderer.h"
// #include "core.h"
#include <stdio.h>
#include <stdlib.h>

GameState gameState;
bool isGameRunning, exitGame;

int main () {

	// Show splash screen
	MainMenu_showSplashScreen();

	char *input;
	isGameRunning = false;
	exitGame = false;
	do {

		// Show main menu
		MainMenu_show(isGameRunning);
		MainMenu_processInput(&gameState, &isGameRunning, &exitGame);

		// Game loop
		bool requestInput = true;
		while (isGameRunning) {

			// Render
			// Renderer_render(&gameState);
			
			// Input
			if (requestInput) {
				input = StringUtils_scan(stdin, '\n');
			} else {
				requestInput = true; // Prevent infinite loops, have to explicitly state to bypass input
			}
			
			// Process
			// Core_process(&gameState, input);
		}

	} while (!exitGame);

	// Prepare to exit - clean up memory
	// GameState_deallocate(&gameState);
	free(input);
	
	return 0;	
}

