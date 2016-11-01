#include "mainmenu.h"
#include "framebuffer.h"
#include "boolean.h"
#include "utilities.h"
#include <stdio.h>

void MainMenu_showSplashScreen() {

	FrameBuffer fb = FrameBuffer_allocate(28, 100);
	FrameBuffer_clear(&fb);

	FrameBuffer_drawRectangle(&fb, Point_make(0, 0), Point_make(27, 99), 'x', GRAY, WHITE, WHITE);
	FrameBuffer_drawRectangle(&fb, Point_make(15, 15), Point_make(20, 20), '*', WHITE, RED, YELLOW);
	FrameBuffer_drawRectangle(&fb, Point_make(18, 18), Point_make(26, 25), '=', BLACK, TRANSPARENT, PURPLE);
	FrameBuffer_drawTextBox(&fb, Point_make(2, 2), Point_make(15, 15), "The quick brown fox jumps over the lazy dog", WHITE, RED);

	FrameBuffer_output(&fb, false);
	delay(2.0);
	FrameBuffer_output(&fb, true);

	delay(12.0);

	FrameBuffer_deallocate(&fb);

	/*clearScreen();
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n                                               <Team name> presents\n");
	delay(1.5);
	clearScreen();
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n                                                   BRIGHTSOULS\n");
	delay(2.0);*/
}

/* Tampilkan main menu di layar: resume game (jika isGameRunning false), new game, load game, save game, exit */
void MainMenu_show(bool isGameRunning) {
	clearScreen();
	printf("\nShow main menu here, Ctrl+C to exit\n");
	delay(0.5);
}

/* Setelah main menu tampil, baca pilihan:
   - resume game (hanya bisa jika *isGameRunning false dan sudah ada nama user di gamestate): set *isGameRunning = true, *exitgame = false
   - new game: baca input nama pemain, GameState_new(gameState, playerName), resume game
   - load game: input nama saveFile, GameState_load(gameState, saveFile), cek validitas saveFile, resume game
   - save game: pilih nama savefile, GameState_save(gameState, saveFile), *isGameRunning = false, *exitGame = false
   - exit: *exitGame = true, *isGameRunning = false */

// void MainMenu_processInput(GameState *gameState, bool *isGameRunning, bool *exitGame) {

//}
