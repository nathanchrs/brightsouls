#include "powerup.h"
#include <stdlib.h>
#include "stringutils.h"

void PowerUp_loadArray(PowerUpArray *powerUps, FILE *fin) {
    int n, i=0;
    fscanf(fin, "%d", &n);
    Array_allocate(powerUps, n);
    powerUps->length = n;

    for (i = 0; i < n; i++) {
        StringUtils_discardCharacters(fin, STRINGUTILS_WHITESPACE);
        powerUps->items[i].powerName = StringUtils_scan(fin, STRINGUTILS_NEWLINE);
        fscanf(fin,"%d", &(powerUps->items[i].location.point.r));
        fscanf(fin,"%d", &(powerUps->items[i].location.point.c));
        fscanf(fin,"%d", &(powerUps->items[i].location.areaId));
        StringUtils_discardCharacters(fin, STRINGUTILS_WHITESPACE);ation
        powerUps->items[i].type = StringUtils_scan(fin, STRINGUTILS_NEWLINE);
        fscanf(fin,"%d", &(powerUps->items[i].bonus));
        StringUtils_discardCharacters(fin, STRINGUTILS_WHITESPACE);
        fscanf(fin,"%c", &(powerUps->items[i].available));
    }
}

void PowerUp_use(const PowerUp *powerUp, Player *player) {
    player->hp += powerUp->type.hpUp;
    player->exp += powerUp->type.expUp;
    player->str += powerUp->type.strUp;
    player->def += powerUp->type.defUp;
}
