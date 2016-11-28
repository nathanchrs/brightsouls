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
}

void Player_save(const Player *player, FILE *fout) {
	IO_writeString(fout, player->name);
	IO_writeNewline(fout);

	IO_writeInteger(fout, player->location.point.r);
	IO_writeInteger(fout, player->location.point.c);
	IO_writeInteger(fout, player->location.areaId);
	IO_writeNewline(fout);

	IO_writeInteger(fout, player->hp);
	IO_writeInteger(fout, player->maxHp);
	IO_writeNewline(fout);

	IO_writeInteger(fout, player->str);
	IO_writeNewline(fout);

	IO_writeInteger(fout, player->def);
	IO_writeNewline(fout);

	IO_writeInteger(fout, player->exp);
	IO_writeInteger(fout, player->maxExp);
	IO_writeNewline(fout);

	IO_writeInteger(fout, player->level);
	IO_writeNewline(fout);
}

/* Redistributes player stats values (usually called after a battle), e.g. level ups */
void Player_normalizeStats(Player *player) {
	if (player->exp > player->maxExp) {
		player->exp -= player->maxExp;
		(player->level)++;
		player->maxExp = (player->maxExp)*3/2;
	}
}

void Player_deallocate(Player *player) {
	StringUtils_deallocate(player->name);
}
