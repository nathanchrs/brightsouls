#include "boolean.h"
// #include "gamestate.h"
#include "mainmenu.h"
// #include "renderer.h"
// #include "core.h"

// GameState gameState;
bool isGameRunning, exitGame;


int main () {

	// Show splash screen
	MainMenu_showSplashScreen();

	isGameRunning = false;
	exitGame = false;
	do {

		// Show main menu
		MainMenu_show(isGameRunning);
		// MainMenu_processInput(&gameState, &isGameRunning, &exitGame);

		// Game loop
		//while (isGameRunning) {

			// Render
			// Renderer_render(&gameState);
			
			// Process
			// Core_process(&gameState);
		//}

	} while (!exitGame);

	// Prepare to exit - clean up memory
	// GameState_destroy(&gameState);
	
	return 0;	
}

