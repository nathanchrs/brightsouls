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
#include "io.h"

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
	FILE *resourceFile = IO_openFile(executableDirectory, "../res/resources.txt");
	if (!resourceFile) {
		fprintf(stderr, "Failed to load resource file from %s../res/resources.txt.", executableDirectory);
		IO_closeFile(resourceFile);
		return 1;
	}
	GameResources_load(&gameResources, resourceFile);
	IO_closeFile(resourceFile);

	// DEBUG: Load initial save file to memory
	char *executableDirectory = getExecutableDirectory(argv[0]);
	FILE *saveFile = IO_openFile(executableDirectory, "../res/initialsave.txt");
	if (!saveFile) {
		fprintf(stderr, "Failed to load save file from %s../res/initialsave.txt.", executableDirectory);
		IO_closeFile(saveFile);
		return 1;
	}
	GameState_load(&gameState, saveFile);
	IO_closeFile(saveFile);

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

	return 0;
}

