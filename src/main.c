#include "boolean.h"
#include "gamestate.h"
#include "mainmenu.h"
#include "stringutils.h"
#include "config.h"
// #include "renderer.h"
// #include "core.h"

GameState gameState;
bool isGameRunning, exitGame;

int main () {

	Config config;
	config.frameBufferHeight = 28;
	config.frameBufferWidth = 100;
	config.useColor = true;

	// Show splash screen
	MainMenu_showSplashScreen(&config);

	char *input;
	isGameRunning = false;
	exitGame = false;
	do {

		// Show main menu
		MainMenu_show(isGameRunning, &config);
		input = StringUtils_scan(stdin, '\n');
		MainMenu_processInput(&gameState, &isGameRunning, &exitGame, input);

		// Game loop
		while (isGameRunning) {

			// Render
			// Renderer_render(&gameState, &config);
			
			// Input
			if (gameState.requestInput) {
				input = StringUtils_scan(stdin, '\n');
			} else {
				gameState.requestInput = true; // Prevent infinite loops, have to explicitly state to bypass input
			}
			
			// Process
			// Core_process(&gameState, input);
		}

	} while (!exitGame);

	// Prepare to exit - clean up memory
	// GameState_deallocate(&gameState);
	StringUtils_deallocate(input);
	
	return 0;	
}

