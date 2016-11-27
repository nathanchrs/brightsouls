#include "mainmenu.h"
#include "framebuffer.h"
#include "boolean.h"
#include "utilities.h"
#include "stringutils.h"
#include "color.h"
#include "list.h"

void MainMenu_showSplashScreen(const Config *config) {

	FrameBuffer fb = FrameBuffer_allocate(config->frameBufferHeight, config->frameBufferWidth, config->useColor);
	FrameBuffer_clear(&fb);
	Color bgcolor_top = WHITE, fgcolor_top = BLACK, bgcolor_bot = WHITE, fgcolor_bot = BLACK;
	
	FrameBuffer_drawTextBox(&fb, Point_make(10, 16), Point_make(10, 100), "__________         .__         .__      __    _________               .__          ", fgcolor_top, bgcolor_top);
	FrameBuffer_drawTextBox(&fb, Point_make(11, 16), Point_make(11, 100), "\\______   \\_______ |__|  ____  |  |__ _/  |_ /   _____/  ____   __ __ |  |   ______", fgcolor_top, bgcolor_top);
	FrameBuffer_drawTextBox(&fb, Point_make(12, 16), Point_make(12, 100), " |    |  _/\\_  __ \\|  | / ___\\ |  |  \\\\   __\\\\_____  \\  /  _ \\ |  |  \\|  |  /  ___/", fgcolor_top, bgcolor_top);
	FrameBuffer_drawTextBox(&fb, Point_make(13, 16), Point_make(13, 100), " |    |   \\ |  | \\/|  |/ /_/  >|   Y  \\|  |  /        \\(  <_> )|  |  /|  |_ \\___ \\ ", fgcolor_bot, bgcolor_bot);
	FrameBuffer_drawTextBox(&fb, Point_make(14, 16), Point_make(14, 100), " |______  / |__|   |__|\\___  / |___|  /|__| /_______  / \\____/ |____/ |____//___  >", fgcolor_bot, bgcolor_bot);
	FrameBuffer_drawTextBox(&fb, Point_make(15, 16), Point_make(15, 100), "        \\/            /_____/       \\/              \\/                          \\/ ", fgcolor_bot, bgcolor_bot);

	FrameBuffer_output(&fb, true);
	delay(1.0);
	FrameBuffer_deallocate(&fb);
}

/* Tampilkan main menu di layar: resume game (jika isGameRunning false), new game, load game, save game, exit */
void MainMenu_show(bool isGameRunning, const Config *config) {
	FrameBuffer fb = FrameBuffer_allocate(config->frameBufferHeight, config->frameBufferWidth, config->useColor);
	Color bgcolor_top = TRANSPARENT, fgcolor_top = WHITE, bgcolor_bot = TRANSPARENT, fgcolor_bot = WHITE;
	int r_temp = 14;
	FrameBuffer_clear(&fb);

	FrameBuffer_drawTextBox(&fb, Point_make(7, 16), Point_make(7, 100), "__________         .__         .__      __    _________               .__          ", fgcolor_top, bgcolor_top);
	FrameBuffer_drawTextBox(&fb, Point_make(8, 16), Point_make(8, 100), "\\______   \\_______ |__|  ____  |  |__ _/  |_ /   _____/  ____   __ __ |  |   ______", fgcolor_top, bgcolor_top);
	FrameBuffer_drawTextBox(&fb, Point_make(9, 16), Point_make(9, 100), " |    |  _/\\_  __ \\|  | / ___\\ |  |  \\\\   __\\\\_____  \\  /  _ \\ |  |  \\|  |  /  ___/", fgcolor_top, bgcolor_top);
	FrameBuffer_drawTextBox(&fb, Point_make(10, 16), Point_make(10, 100), " |    |   \\ |  | \\/|  |/ /_/  >|   Y  \\|  |  /        \\(  <_> )|  |  /|  |_ \\___ \\ ", fgcolor_top, bgcolor_top);
	FrameBuffer_drawTextBox(&fb, Point_make(11, 16), Point_make(11, 100), " |______  / |__|   |__|\\___  / |___|  /|__| /_______  / \\____/ |____/ |____//___  >", fgcolor_top, bgcolor_top);
	FrameBuffer_drawTextBox(&fb, Point_make(12, 16), Point_make(12, 100), "        \\/            /_____/       \\/              \\/                          \\/ ", fgcolor_top, bgcolor_top);


	if(isGameRunning) {
		 // jika isGameRunning, maka ada 1 tambahan menu entry yaitu resume
		FrameBuffer_drawTextBox(&fb, Point_make(r_temp, 46), Point_make(r_temp, 70), "Start/Resume (:resume)", fgcolor_bot, bgcolor_bot);
		r_temp = 15;
	}
	FrameBuffer_drawTextBox(&fb, Point_make(r_temp, 46), Point_make(r_temp, 70), "New Game (new)", fgcolor_bot, bgcolor_bot);
	FrameBuffer_drawTextBox(&fb, Point_make(r_temp+1, 46), Point_make(r_temp+1, 70), "Load Game (load)", fgcolor_bot, bgcolor_bot);
	if(isGameRunning) {
		FrameBuffer_drawTextBox(&fb, Point_make(r_temp+2, 46), Point_make(r_temp+2, 70), "Save Game (save)", fgcolor_bot, bgcolor_bot);
		r_temp++;
	}
	FrameBuffer_drawTextBox(&fb, Point_make(r_temp+2, 46), Point_make(r_temp+3, 70), "Exit Game (exit)", fgcolor_bot, bgcolor_bot);
	
	FrameBuffer_setInputPrompt(&fb, "Input command >> ");

	FrameBuffer_output(&fb, true);
	FrameBuffer_deallocate(&fb);
}
