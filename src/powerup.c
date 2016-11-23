#include "powerup.h"
#include <stdlib.h>
#include "stringutils.h"

void Powerup_load(Powerup *powerup, FILE *fin) {
    int n, i=0;
    fscanf(fin, "%d", &n);
    Array_allocate(powerup, n);
    powerup->length = n;

    for (i = 0; i < n; i++) {
        StringUtils_discardCharacters(fin, STRINGUTILS_WHITESPACE);
        powerup->items[i].powerName = StringUtils_scan(fin, STRINGUTILS_NEWLINE);
        fscanf(fin,"%d", &(powerup->items[i].loc.point.r));
        fscanf(fin,"%d", &(powerup->items[i].loc.point.c));
        fscanf(fin,"%d", &(powerup->items[i].loc.areaId));
        StringUtils_discardCharacters(fin, STRINGUTILS_WHITESPACE);
        powerup->items[i].type = StringUtils_scan(fin, STRINGUTILS_NEWLINE);
        fscanf(fin,"%d", &(powerup->items[i].bonus));
        StringUtils_discardCharacters(fin, STRINGUTILS_WHITESPACE);
        fscanf(fin,"%c", &(powerup->items[i].available));
    }
}

void Powerup_add(PowerType powerup, Player *player) {
    if(StringUtils_strcmpi(powerup.type,"hp") == 0) {
        player->hp += powerup.bonus;
    } else if(StringUtils_strcmpi(powerup.type,"str") == 0) {
        player->str += powerup.bonus;
    } else if(StringUtils_strcmpi(powerup.type,"def") == 0) {
        player->def += powerup.bonus;
    } else if(StringUtils_strcmpi(powerup.type,"exp") == 0) {
        player->exp += powerup.bonus;
    }
}