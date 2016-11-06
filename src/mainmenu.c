#include "mainmenu.h"
#include "framebuffer.h"
#include "boolean.h"
#include "utilities.h"
#include "stringutils.h"
#include "color.h"

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
		FrameBuffer_drawTextBox(&fb, Point_make(13, 7), Point_make(13, 142), "     ...     ..                      .                                 s       .x+=:.                                    ..    .x+=:.   ", fgcolor_top, bgcolor_top);
		FrameBuffer_drawTextBox(&fb, Point_make(14, 7), Point_make(14, 142), "  .=*8888x <\"?88h.                  @88>                .uef^\"        :8      z`    ^%                             x .d88\"    z`    ^%%  ", fgcolor_top, bgcolor_top);
		FrameBuffer_drawTextBox(&fb, Point_make(15, 7), Point_make(15, 142), " X>  '8888H> '8888      .u    .     %%8P               :d88E          .88         .   <k        u.      x.    .      5888R        .   <k ", fgcolor_top, bgcolor_top);
		FrameBuffer_drawTextBox(&fb, Point_make(16, 7), Point_make(16, 142), "'88h. `8888   8888    .d88B :@8c     .         uL     `888E         :888ooo    .@8Ned8\"  ...ue888b   .@88k  z88u    '888R      .@8Ned8\" ", fgcolor_top, bgcolor_top);
		FrameBuffer_drawTextBox(&fb, Point_make(17, 7), Point_make(17, 142), "'8888 '8888    \"88>  =\"8888f8888r  .@88u   .ue888Nc..  888E .z8k  -*8888888  .@^%%8888\"   888R Y888r ~\"8888 ^8888     888R    .@^%%8888\"  ", fgcolor_top, bgcolor_top);
		FrameBuffer_drawTextBox(&fb, Point_make(18, 7), Point_make(18, 142), " `888 '8888.xH888x.    4888>'88\"  ''888E` d88E`\"888E`  888E~?888L   8888    x88:  `)8b.  888R I888>   8888  888R     888R   x88:  `)8b. ", fgcolor_top, bgcolor_top);
		FrameBuffer_drawTextBox(&fb, Point_make(19, 7), Point_make(19, 142), "   X\" :88*~  `*8888>   4888> '      888E  888E  888E   888E  888E   8888    8888N=*8888  888R I888>   8888  888R     888R   8888N=*8888 ", fgcolor_top, bgcolor_top);
		FrameBuffer_drawTextBox(&fb, Point_make(20, 7), Point_make(20, 142), " ~\"   !\"`      \"888>   4888>        888E  888E  888E   888E  888E   8888     %%8\"    R88  888R I888>   8888  888R     888R    %%8\"    R88 ", fgcolor_bot, bgcolor_bot);
		FrameBuffer_drawTextBox(&fb, Point_make(21, 7), Point_make(21, 142), "  .H8888h.      ?88   .d888L .+     888E  888E  888E   888E  888E  .8888Lu=   @8Wou 9%  u8888cJ888    8888 ,888B .   888R     @8Wou 9%%  ", fgcolor_bot, bgcolor_bot);
		FrameBuffer_drawTextBox(&fb, Point_make(22, 7), Point_make(22, 142), " :\"^\"88888h.    '!    ^\"8888*\"      888&  888& .888E   888E  888E  ^%%888*   .888888P`    \"*888*P\"    \"8888Y 8888\"   .888B . .888888P`   ", fgcolor_bot, bgcolor_bot);
		FrameBuffer_drawTextBox(&fb, Point_make(23, 7), Point_make(23, 142), " ^    \"88888hx.+\"        \"Y\"        R888\" *888\" 888&  m888N= 888>    'Y\"    `   ^\"F        'Y\"        `Y\"   'YP     ^*888%%  `   ^\"F     ", fgcolor_bot, bgcolor_bot);
		FrameBuffer_drawTextBox(&fb, Point_make(24, 7), Point_make(24, 142), "        ^\"**""                       ""    `\"   \"888E  `Y\"   888                                                      \"%%                   ", fgcolor_bot, bgcolor_bot);
		FrameBuffer_drawTextBox(&fb, Point_make(25, 7), Point_make(25, 142), "                                          4888~  J8%%        @%%                                                                          ", fgcolor_bot, bgcolor_bot);
		FrameBuffer_drawTextBox(&fb, Point_make(26, 7), Point_make(26, 142), "                                           ^\"===*\"`       :\"                                                                            ", fgcolor_bot, bgcolor_bot);
	//FrameBuffer_setInputPrompt(&fb, "Splash screen\n");
		FrameBuffer_output(&fb, config->useColor);
	//FrameBuffer_output(&fb, false);
		delay(2.0);
		x += 2.0;
	}

	FrameBuffer_drawTextBox(&fb, Point_make(28, 65), Point_make(28, 86), "Better with Fullscreen", WHITE, BLACK);
	FrameBuffer_output(&fb, config->useColor);
	delay(2.0);
	FrameBuffer_deallocate(&fb);
}

/* Tampilkan main menu di layar: resume game (jika isGameRunning false), new game, load game, save game, exit */
void MainMenu_show(const bool isGameRunning, const Config *config) {
	FrameBuffer fb = FrameBuffer_allocate(config->frameBufferHeight, config->frameBufferWidth);
	Color bgcolor_top = TRANSPARENT, fgcolor_top = WHITE, bgcolor_bot = TRANSPARENT, fgcolor_bot = WHITE;
	int r_temp = 22;
	FrameBuffer_clear(&fb);

	//FrameBuffer_drawRectangle(&fb, Point_make(1, 1), Point_make(37, 149), 'x', GRAY, WHITE, WHITE);
	FrameBuffer_drawTextBox(&fb, Point_make(8, 24), Point_make(8, 126), "@@@@@@@   @@@@@@@   @@@   @@@@@@@@  @@@  @@@  @@@@@@@   @@@@@@    @@@@@@   @@@  @@@  @@@        @@@@@@", fgcolor_top, bgcolor_top);
	FrameBuffer_drawTextBox(&fb, Point_make(9, 24), Point_make(9, 126), "@@@@@@@@  @@@@@@@@  @@@  @@@@@@@@@  @@@  @@@  @@@@@@@  @@@@@@@   @@@@@@@@  @@@  @@@  @@@       @@@@@@@", fgcolor_top, bgcolor_top);
	FrameBuffer_drawTextBox(&fb, Point_make(10, 24), Point_make(10, 126), "@@!  @@@  @@!  @@@  @@!  !@@        @@!  @@@    @@!    !@@       @@!  @@@  @@!  @@@  @@!       !@@", fgcolor_top, bgcolor_top);
	FrameBuffer_drawTextBox(&fb, Point_make(11, 24), Point_make(11, 126), "!@   @!@  !@!  @!@  !@!  !@!        !@!  @!@    !@!    !@!       !@!  @!@  !@!  @!@  !@!       !@!", fgcolor_top, bgcolor_top);
	FrameBuffer_drawTextBox(&fb, Point_make(12, 24), Point_make(12, 126), "@!@!@!@   @!@!!@!   !!@  !@! @!@!@  @!@!@!@!    @!!    !!@@!!    @!@  !@!  @!@  !@!  @!!       !!@@!!", fgcolor_top, bgcolor_top);
	FrameBuffer_drawTextBox(&fb, Point_make(13, 24), Point_make(13, 126), "!!!@!!!!  !!@!@!    !!!  !!! !!@!!  !!!@!!!!    !!!     !!@!!!   !@!  !!!  !@!  !!!  !!!        !!@!!!", fgcolor_bot, bgcolor_bot);
	FrameBuffer_drawTextBox(&fb, Point_make(14, 24), Point_make(14, 126), "!!:  !!!  !!: :!!   !!:  :!!   !!:  !!:  !!!    !!:         !:!  !!:  !!!  !!:  !!!  !!:            !:!", fgcolor_bot, bgcolor_bot);
	FrameBuffer_drawTextBox(&fb, Point_make(15, 24), Point_make(15, 126), ":!:  !:!  :!:  !:!  :!:  :!:   !::  :!:  !:!    :!:        !:!   :!:  !:!  :!:  !:!   :!:          !:!", fgcolor_bot, bgcolor_bot);
	FrameBuffer_drawTextBox(&fb, Point_make(16, 24), Point_make(16, 126), " :: ::::  ::   :::   ::   ::: ::::  ::   :::     ::    :::: ::   ::::: ::  ::::: ::   :: ::::  :::: ::", fgcolor_bot, bgcolor_bot);
	FrameBuffer_drawTextBox(&fb, Point_make(17, 24), Point_make(17, 126), ":: : ::    :   : :  :     :: :: :    :   : :     :     :: : :     : :  :    : :  :   : :: : :  :: : : ", fgcolor_bot, bgcolor_bot);


	if(isGameRunning) {
		 // jika isGameRunning, maka ada 1 tambahan menu entry yaitu resume
		//FrameBuffer_drawRectangle(&fb, Point_make(18, 61), Point_make(24, 100), 'o', GRAY, TRANSPARENT, WHITE);
		FrameBuffer_drawTextBox(&fb, Point_make(r_temp, 58), Point_make(r_temp, 80), "Resume		(:resume)", fgcolor_bot, bgcolor_bot);
		r_temp = 23;
	}
	FrameBuffer_drawTextBox(&fb, Point_make(r_temp, 58), Point_make(r_temp, 80), "New Game		(:new)", fgcolor_bot, bgcolor_bot);
	FrameBuffer_drawTextBox(&fb, Point_make(r_temp+1, 58), Point_make(r_temp+1, 80), "Load Game		(:load)", fgcolor_bot, bgcolor_bot);
	FrameBuffer_drawTextBox(&fb, Point_make(r_temp+2, 58), Point_make(r_temp+2, 80), "Credit 		(:credit)", fgcolor_bot, bgcolor_bot);
	FrameBuffer_drawTextBox(&fb, Point_make(r_temp+3, 58), Point_make(r_temp+3, 80), "Exit Game		(:exit)", fgcolor_bot, bgcolor_bot);
	//FrameBuffer_drawTextBox(&fb, Point_make(2, 2), Point_make(15, 15), "Main menu", WHITE, RED);
	//FrameBuffer_drawTextBox(&fb, Point_make(10, 10), Point_make(20, 20), "Enter [exit] or [quit] to exit.", BLACK, TRANSPARENT);
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

	} else if(StringUtils_strcmpi(input, "PAUSE") == 0) {
		*isGameRunning = true; // just for testing reason, not the real purpose, still not yet implemented
	} else {

	}
}
