#include "boolean.h"
#include "gamestate.h"
#include "gameresources.h"
#include "mainmenu.h"
#include "stringutils.h"
#include "config.h"
#include "framebuffer.h"
#include "renderer.h"
// #include "core.h"
// 
#include "utilities.h"
#include "skilltree.h"

GameState gameState;
GameResources gameResources;
bool isGameRunning, exitGame;

int main () {

	Config config;
	config.frameBufferHeight = 28;
	config.frameBufferWidth = 100;
	config.useColor = true;

	// Show splash screen
	MainMenu_showSplashScreen(&config);

	// Load resources to memory
	// GameResources_load(&gameResources, "resources.txt");
	
	// DEBUG
	FILE *fin = fopen("./test/skilltree2.in", "r");
	SkillTree_load(&(gameResources.skillTree), fin);

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
				gameState.requestInput = true; // Prevent infinite loops, have to explicitly state to bypass input
			}
			
			// DEBUG
			delay(1.0);

			// Process
			// Core_process(&gameState, &gameResources, input);
		}
		FrameBuffer_deallocate(&frameBuffer);

	} while (!exitGame);

	// Prepare to exit - clean up memory
	// GameState_deallocate(&gameState);
	// GameResources_deallocate(&gameResources);
	StringUtils_deallocate(input);
	
	return 0;	
}

