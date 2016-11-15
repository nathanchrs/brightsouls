#include "mainmenu.h"
#include "framebuffer.h"
#include "boolean.h"
#include "utilities.h"
#include "stringutils.h"
#include "color.h"
#include "list.h"

void MainMenu_showSplashScreen(const Config *config) {

	FrameBuffer fb = FrameBuffer_allocate(config->frameBufferHeight, config->frameBufferWidth);
	FrameBuffer_clear(&fb);
	Color bgcolor_top = WHITE, fgcolor_top = BLACK, bgcolor_bot = WHITE, fgcolor_bot = BLACK;
	float x = 0.0;
	//FrameBuffer_drawRectangle(&fb, Point_make(1, 1), Point_make(37, 149), 'x', WHITE, WHITE, WHITE);

	//FrameBuffer_drawRectangle(&fb, Point_make(15, 15), Point_make(20, 20), '*', WHITE, RED, YELLOW);
	//FrameBuffer_drawRectangle(&fb, Point_make(18, 18), Point_make(26, 25), '=', BLACK, TRANSPARENT, PURPLE);
	while(x<=6.0) {
		if(x == 2.0) {
			fgcolor_top = WHITE;
			bgcolor_top = BLACK;
		} else if(x == 4.0) {
			fgcolor_bot = WHITE;
			bgcolor_bot = BLACK;
		} else if(x == 6.0) {
			fgcolor_top = bgcolor_top = fgcolor_bot = bgcolor_bot = TRANSPARENT;
		}
		FrameBuffer_drawTextBox(&fb, Point_make(10, 16), Point_make(10, 100), "__________         .__         .__      __    _________               .__          ", fgcolor_top, bgcolor_top);
		FrameBuffer_drawTextBox(&fb, Point_make(11, 16), Point_make(11, 100), "\\______   \\_______ |__|  ____  |  |__ _/  |_ /   _____/  ____   __ __ |  |   ______", fgcolor_top, bgcolor_top);
		FrameBuffer_drawTextBox(&fb, Point_make(12, 16), Point_make(12, 100), " |    |  _/\\_  __ \\|  | / ___\\ |  |  \\\\   __\\\\_____  \\  /  _ \\ |  |  \\|  |  /  ___/", fgcolor_top, bgcolor_top);
		FrameBuffer_drawTextBox(&fb, Point_make(13, 16), Point_make(13, 100), " |    |   \\ |  | \\/|  |/ /_/  >|   Y  \\|  |  /        \\(  <_> )|  |  /|  |_ \\___ \\ ", fgcolor_bot, bgcolor_bot);
		FrameBuffer_drawTextBox(&fb, Point_make(14, 16), Point_make(14, 100), " |______  / |__|   |__|\\___  / |___|  /|__| /_______  / \\____/ |____/ |____//___  >", fgcolor_bot, bgcolor_bot);
		FrameBuffer_drawTextBox(&fb, Point_make(15, 16), Point_make(15, 100), "        \\/            /_____/       \\/              \\/                          \\/ ", fgcolor_bot, bgcolor_bot);
	//FrameBuffer_setInputPrompt(&fb, "Splash screen\n");
		FrameBuffer_output(&fb, config->useColor);
	//FrameBuffer_output(&fb, false);
		delay(2.0);
		x += 2.0;
	}
	delay(2.0);
	FrameBuffer_deallocate(&fb);
}

/* Tampilkan main menu di layar: resume game (jika isGameRunning false), new game, load game, save game, exit */
void MainMenu_show(const bool isGameRunning, const Config *config) {
	FrameBuffer fb = FrameBuffer_allocate(config->frameBufferHeight, config->frameBufferWidth);
	Color bgcolor_top = TRANSPARENT, fgcolor_top = WHITE, bgcolor_bot = TRANSPARENT, fgcolor_bot = WHITE;
	int r_temp = 14;
	FrameBuffer_clear(&fb);

	//FrameBuffer_drawRectangle(&fb, Point_make(1, 1), Point_make(37, 149), 'x', GRAY, WHITE, WHITE);
		FrameBuffer_drawTextBox(&fb, Point_make(7, 16), Point_make(7, 100), "__________         .__         .__      __    _________               .__          ", fgcolor_top, bgcolor_top);
		FrameBuffer_drawTextBox(&fb, Point_make(8, 16), Point_make(8, 100), "\\______   \\_______ |__|  ____  |  |__ _/  |_ /   _____/  ____   __ __ |  |   ______", fgcolor_top, bgcolor_top);
		FrameBuffer_drawTextBox(&fb, Point_make(9, 16), Point_make(9, 100), " |    |  _/\\_  __ \\|  | / ___\\ |  |  \\\\   __\\\\_____  \\  /  _ \\ |  |  \\|  |  /  ___/", fgcolor_top, bgcolor_top);
		FrameBuffer_drawTextBox(&fb, Point_make(10, 16), Point_make(10, 100), " |    |   \\ |  | \\/|  |/ /_/  >|   Y  \\|  |  /        \\(  <_> )|  |  /|  |_ \\___ \\ ", fgcolor_top, bgcolor_top);
		FrameBuffer_drawTextBox(&fb, Point_make(11, 16), Point_make(11, 100), " |______  / |__|   |__|\\___  / |___|  /|__| /_______  / \\____/ |____/ |____//___  >", fgcolor_top, bgcolor_top);
		FrameBuffer_drawTextBox(&fb, Point_make(12, 16), Point_make(12, 100), "        \\/            /_____/       \\/              \\/                          \\/ ", fgcolor_top, bgcolor_top);


	if(isGameRunning) {
		 // jika isGameRunning, maka ada 1 tambahan menu entry yaitu resume
		//FrameBuffer_drawRectangle(&fb, Point_make(18, 61), Point_make(24, 100), 'o', GRAY, TRANSPARENT, WHITE);
		FrameBuffer_drawTextBox(&fb, Point_make(r_temp, 46), Point_make(r_temp, 70), "Resume		(:resume)", fgcolor_bot, bgcolor_bot);
		r_temp = 15;
	}
	FrameBuffer_drawTextBox(&fb, Point_make(r_temp, 46), Point_make(r_temp, 70), "New Game		(:new)", fgcolor_bot, bgcolor_bot);
	FrameBuffer_drawTextBox(&fb, Point_make(r_temp+1, 46), Point_make(r_temp+1, 70), "Load Game		(:load)", fgcolor_bot, bgcolor_bot);
	FrameBuffer_drawTextBox(&fb, Point_make(r_temp+2, 46), Point_make(r_temp+2, 70), "Credit 		(:credit)", fgcolor_bot, bgcolor_bot);
	FrameBuffer_drawTextBox(&fb, Point_make(r_temp+3, 46), Point_make(r_temp+3, 70), "Exit Game		(:exit)", fgcolor_bot, bgcolor_bot);
	//FrameBuffer_drawTextBox(&fb, Point_make(2, 2), Point_make(15, 15), "Main menu", WHITE, RED);
	//FrameBuffer_drawTextBox(&fb, Point_make(10, 10), Point_make(20, 20), "Enter [exit] or [quit] to exit.", BLACK, TRANSPARENT);
	FrameBuffer_setInputPrompt(&fb, "Input commands >> ");

	FrameBuffer_output(&fb, config->useColor);
	FrameBuffer_deallocate(&fb);
}

/* Setelah main menu tampil, baca pilihan:
   - resume game (hanya bisa jika *isGameRunning false dan sudah ada nama user di gamestate): set *isGameRunning = true, *exitgame = false
   - new game: baca input nama pemain, GameState_new(gameState, playerName), resume game
   - load game: input nama saveFile, GameState_load(gameState, saveFile), cek validitas saveFile, resume game
   - save game: pilih nama savefile, GameState_save(gameState, saveFile), *isGameRunning = false, *exitGame = false
   - exit: *exitGame = true, *isGameRunning = false */

void MainMenu_processInput(GameState *gameState, bool *isGameRunning, bool *exitGame, const char *input) {
	LIST(char*) command;
	List_initialize(&command);

	if (StringUtils_strcmpi(input, "EXIT") == 0 || StringUtils_strcmpi(input, "QUIT") == 0) {
		*isGameRunning = false;
		*exitGame = true;

	} else if(StringUtils_strcmpi(input, "PAUSE") == 0) {
		*isGameRunning = true; // just for testing reason, not the real purpose, still not yet implemented
	} else {

	}
}
