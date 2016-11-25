#include "powerup.h"
#include "io.h"

void PowerUpArray_load(PowerUpArray *powerUps, FILE *fin) {
    int n, i;
    n = IO_readInteger(fin);
    Array_allocate(powerUps, n);
    powerUps->length = n;

    for (i = 0; i < n; i++) {
        powerUps->items[i].typeId = IO_readInteger(fin);
        powerUps->items[i].location.point.r = IO_readInteger(fin);
        powerUps->items[i].location.point.c = IO_readInteger(fin);
        powerUps->items[i].location.areaId = IO_readInteger(fin);
        powerUps->items[i].available = IO_readInteger(fin);
    }
}

void PowerUpTypeArray_load(PowerUpTypeArray *powerUpTypes, FILE *fin) {
    int n, i;
    n = IO_readInteger(fin);
    Array_allocate(powerUpTypes, n);
    powerUpTypes->length = n;

    for (i = 0; i < n; i++) {
        powerUpTypes->items[i].name = IO_readString(fin);
        powerUpTypes->items[i].hpUp = IO_readInteger(fin);
        powerUpTypes->items[i].expUp = IO_readInteger(fin);
        powerUpTypes->items[i].strUp = IO_readInteger(fin);
        powerUpTypes->items[i].defUp = IO_readInteger(fin);
    }
}

void PowerUp_use(const PowerUpTypeArray *powerUpTypes, const PowerUp *powerUp, Player *player) {
    player->hp += powerUpTypes->items[powerUp->typeId].hpUp;
    player->exp += powerUpTypes->items[powerUp->typeId].expUp;
    player->str += powerUpTypes->items[powerUp->typeId].strUp;
    player->def += powerUpTypes->items[powerUp->typeId].defUp;
}

void PowerUpTypeArray_deallocate(PowerUpTypeArray *powerUpTypes) {
    Array_deallocate(powerUpTypes);
}

void PowerUpArray_deallocate(PowerUpArray *powerUps) {
    Array_deallocate(powerUps);
}