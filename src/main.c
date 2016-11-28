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
#include "location.h"

GameState gameState;
GameResources gameResources;
bool isGameRunning, exitGame;
bool isGameStateLoaded;
char *playerName;

int main (int argc, char *argv[]) {
	char *executableDirectory = getExecutableDirectory(argv[0]);

	Config config;
	config.frameBufferHeight = 30;
	config.frameBufferWidth = 120;
	config.useColor = true;

	// Load resources to memory
	FILE *resourceFile = IO_openFile(executableDirectory, "../res/resources.txt");
	if (!resourceFile) {
		fprintf(stderr, "Failed to load resource file from %s../res/resources.txt.", executableDirectory);
		if (resourceFile) IO_closeFile(resourceFile);
		return 1;
	}
	GameResources_load(&gameResources, resourceFile);
	IO_closeFile(resourceFile);

	// Show splash screen
	MainMenu_showSplashScreen(&config);

	char *input = NULL;
	isGameRunning = false;
	exitGame = false;
	playerName = NULL;
	isGameStateLoaded = false;
	do {

		// Show main menu
		MainMenu_show(isGameStateLoaded, &config);
		input = StringUtils_scan(stdin, "\n");

		// Process main menu input
		
		if (StringUtils_strcmpi(input, "exit") == 0 || StringUtils_strcmpi(input, "quit") == 0) {
			isGameRunning = false;
			exitGame = true;
		} else if (isGameStateLoaded && (StringUtils_strcmpi(input, "start") == 0 || StringUtils_strcmpi(input, "resume") == 0)) {
			isGameRunning = true;
			exitGame = false;
		} else if (StringUtils_strcmpi(input, "new") == 0) {
			
			printf("Input player name (must be alphanumeric, no whitespace): ");
			playerName = StringUtils_scan(stdin, IO_WHITESPACE);

			if (StringUtils_check(playerName, StringUtils_isAlphanumeric)) {
			
				// Load initial save file (new game) to memory
				FILE *saveFile = IO_openFile(executableDirectory, "../res/initialsave.txt");
				if (!saveFile) {
					fprintf(stderr, "Failed to load save file from %s../res/initialsave.txt.\n", executableDirectory);
					if (saveFile) IO_closeFile(saveFile);
					delay(2.0);
				} else {
					GameState_load(&gameState, saveFile);
					IO_closeFile(saveFile);
					
					LocationEdgeArray_permute(&(gameState.locationEdges));
					gameState.player.name = StringUtils_clone(playerName);
					isGameRunning = true;
					isGameStateLoaded = true;
				}

			} else {
				printf("Invalid player name.\n");
				delay(2.0);
			}
			
		} else if (isGameStateLoaded && StringUtils_strcmpi(input, "save") == 0) {

			FILE *saveFile = IO_openFileForWrite(executableDirectory, gameState.player.name);
			if (!saveFile) {
				fprintf(stderr, "Failed to save to file %s.", gameState.player.name);
				if (saveFile) IO_closeFile(saveFile);
				delay(2.0);
			} else {
				GameState_save(&gameState, saveFile);
				IO_closeFile(saveFile);

				printf("Game saved.\n");
				delay(2.0);
			}

		} else if (StringUtils_strcmpi(input, "load") == 0) {

			printf("Input player name (must be valid filename, no whitespace): ");
			playerName = StringUtils_scan(stdin, IO_WHITESPACE);

			// Load player save file to memory
			FILE *saveFile = IO_openFile(executableDirectory, playerName);
			if (!saveFile) {
				fprintf(stderr, "Failed to load save file from %s.\n", playerName);
				if (saveFile) IO_closeFile(saveFile);
				delay(2.0);
			} else {
				GameState_load(&gameState, saveFile);
				IO_closeFile(saveFile);

				isGameStateLoaded = true;
				isGameRunning = true;
				exitGame = false;
			}

		} else {
			printf("Invalid command.\n");
			delay(1.0);
		}
		
		// Game loop
		FrameBuffer frameBuffer = FrameBuffer_allocate(config.frameBufferHeight, config.frameBufferWidth, config.useColor);
		while (isGameRunning) {

			// Render
			Renderer_render(&frameBuffer, &gameState, &gameResources);

			// Input
			input = StringUtils_scan(stdin, "\n");
			if (StringUtils_strcmpi(input, "pause") == 0 || StringUtils_strcmpi(input, "exit") == 0 || StringUtils_strcmpi(input, "quit") == 0) {
				// Exit to main menu
				isGameRunning = false;
				break;
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
	StringUtils_deallocate(playerName);

	return 0;
}

