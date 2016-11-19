#include "boolean.h"
#include "gamestate.h"
#include "gameresources.h"
#include "mainmenu.h"
#include "stringutils.h"
#include "config.h"
#include "framebuffer.h"
#include "renderer.h"
#include "utilities.h"
#include "core.h"
#include <stdio.h>

GameState gameState;
GameResources gameResources;
bool isGameRunning, exitGame;
bool fileRead;

int main (int argc, char *argv[]) {

	Config config;
	config.frameBufferHeight = 30;
	config.frameBufferWidth = 120;
	config.useColor = true;

	// Load resources to memory
	char *executableDirectory = getExecutableDirectory(argv[0]);
	char *resourcePath = StringUtils_concat(executableDirectory, "../res/resources.txt");
	fileRead = GameResources_load(&gameResources, resourcePath);
	if (!fileRead) {
		fprintf(stderr, "Failed to load resources from %s\n", resourcePath);
		return 1;
	}


	// DEBUG
	char *initialSavePath = StringUtils_concat(executableDirectory, "../res/initialsave.txt");
	fileRead = GameState_load(&gameState, initialSavePath);
	if (!fileRead) {
		fprintf(stderr, "Failed to load game state from %s %s\n", executableDirectory, initialSavePath);
		return 1;
	}

	// DEBUG
	gameState.currentPhase = EXPLORATION;

	// Show splash screen
	MainMenu_showSplashScreen(&config);

	char *input;
	isGameRunning = false;
	exitGame = false;
	do {

		// Show main menu
		MainMenu_show(isGameRunning, &config);
		input = StringUtils_scan(stdin, "\n");
		MainMenu_processInput(&gameState, &isGameRunning, &exitGame, input);

		// Game loop
		FrameBuffer frameBuffer = FrameBuffer_allocate(config.frameBufferHeight, config.frameBufferWidth, config.useColor);
		while (isGameRunning) {

			// Render
			Renderer_render(&frameBuffer, &gameState, &gameResources);
			
			// Input
			if (gameState.requestInput) {
				input = StringUtils_scan(stdin, "\n");
			} else {
				// If requestInput is false, then the program will not wait for input. Useful for animations, etc.
				gameState.requestInput = true; // Prevent infinite loops, have to explicitly state to bypass input
			}

			// Process
			Core_process(&gameState, &gameResources, input);
		}
		FrameBuffer_deallocate(&frameBuffer);

	} while (!exitGame);

	// Prepare to exit - clean up memory
	GameState_deallocate(&gameState);
	GameResources_deallocate(&gameResources);
	StringUtils_deallocate(input);

	StringUtils_deallocate(executableDirectory);
	StringUtils_deallocate(resourcePath);
	StringUtils_deallocate(initialSavePath);

	return 0;	
}

