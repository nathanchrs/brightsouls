#include "mainmenu.h"
#include "framebuffer.h"
#include "boolean.h"
#include "utilities.h"
#include "stringutils.h"

void MainMenu_showSplashScreen(const Config *config) {

	FrameBuffer fb = FrameBuffer_allocate(config->frameBufferHeight, config->frameBufferWidth, config->useColor);
	FrameBuffer_clear(&fb);

	FrameBuffer_drawRectangle(&fb, Point_make(0, 0), Point_make(27, 99), 'x', GRAY, WHITE, WHITE);
	FrameBuffer_drawRectangle(&fb, Point_make(15, 15), Point_make(20, 20), '*', WHITE, RED, YELLOW);
	FrameBuffer_drawRectangle(&fb, Point_make(18, 18), Point_make(26, 25), '=', BLACK, TRANSPARENT, PURPLE);
	FrameBuffer_drawTextBox(&fb, Point_make(2, 2), Point_make(15, 15), "The quick brown fox jumps over the lazy dog", WHITE, RED);
	FrameBuffer_setInputPrompt(&fb, "Splash screen ");

	FrameBuffer_output(&fb, false);
	//delay(2.0);
	FrameBuffer_output(&fb, config->useColor);
	delay(0.5);

	FrameBuffer_deallocate(&fb);
}

/* Tampilkan main menu di layar: resume game (jika isGameRunning false), new game, load game, save game, exit */
void MainMenu_show(const bool isGameRunning, const Config *config) {
	FrameBuffer fb = FrameBuffer_allocate(config->frameBufferHeight, config->frameBufferWidth, config->useColor);
	FrameBuffer_clear(&fb);

	FrameBuffer_drawRectangle(&fb, Point_make(0, 0), Point_make(27, 99), 'x', GRAY, WHITE, WHITE);
	FrameBuffer_drawTextBox(&fb, Point_make(2, 2), Point_make(15, 15), "Main menu", WHITE, RED);
	FrameBuffer_drawTextBox(&fb, Point_make(10, 10), Point_make(20, 20), "Enter [exit] or [quit] to exit.", BLACK, TRANSPARENT);
	FrameBuffer_setInputPrompt(&fb, "Select menu option >> ");

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
	if (StringUtils_strcmpi(input, "EXIT") == 0 || StringUtils_strcmpi(input, "QUIT") == 0) {
		*isGameRunning = false;
		*exitGame = true;
		
	} else if (StringUtils_strcmpi(input, "START") == 0) {
		*isGameRunning = true;
		*exitGame = false;
	}
}
