#include "player.h"
#include "io.h"
#include "stringutils.h"

void Player_load(Player *player, FILE *fin) {
	player->name = IO_readString(fin);

	player->location.point.r = IO_readInteger(fin);
	player->location.point.c = IO_readInteger(fin);
	player->location.areaId = IO_readInteger(fin);

	player->hp = IO_readInteger(fin);
	player->maxHp = IO_readInteger(fin);
	player->str = IO_readInteger(fin);
	player->def = IO_readInteger(fin);
	player->exp = IO_readInteger(fin);
	player->maxExp = IO_readInteger(fin);
	player->level = IO_readInteger(fin);

	MoveQueue_load(&(player->moveQueue), fin);
}

void Player_save(const Player *player, FILE *fout) {

}

void Player_deallocate(Player *player) {
	StringUtils_deallocate(player->name);
	MoveQueue_deallocate(&(player->moveQueue));
}
