#include <assert.h>
#include <stdio.h>
#include "../src/powerup.h"
#include "../src/stringutils.h"

void testPowerUp(const char *executableDirectory) {
    printf("  Testing PowerUp...\n");

    PowerUpTypeArray powerUpTypes;
    PowerUpArray powerUps;

    FILE *fin = IO_openFile(executableDirectory, "../test/powerup.in");
    assert(fin != NULL);
    PowerUpTypeArray_load(&powerUpTypes, fin);
    PowerUpArray_load(&powerUps, fin);
    IO_closeFile(fin);

    assert(powerUpTypes.length == 4);
    assert(powerUps.length == 3);

    assert(StringUtils_strcmpi(powerUpTypes.items[0].name, "powerup") == 0);
    assert(StringUtils_strcmpi(powerUpTypes.items[1].name, "second powerup") == 0);
    assert(StringUtils_strcmpi(powerUpTypes.items[2].name, "powerup ke-3") == 0);
    assert(StringUtils_strcmpi(powerUpTypes.items[3].name, "last") == 0);

    assert(powerUpTypes.items[0].hpUp == 1);
    assert(powerUpTypes.items[1].hpUp == 5);
    assert(powerUpTypes.items[2].hpUp == 0);
    assert(powerUpTypes.items[3].hpUp == 100);

    assert(powerUpTypes.items[0].expUp == 2);
    assert(powerUpTypes.items[1].expUp == 6);
    assert(powerUpTypes.items[2].expUp == 0);
    assert(powerUpTypes.items[3].expUp == 90);

    assert(powerUpTypes.items[0].strUp == 3);
    assert(powerUpTypes.items[1].strUp == 7);
    assert(powerUpTypes.items[2].strUp == 0);
    assert(powerUpTypes.items[3].strUp == 80);

    assert(powerUpTypes.items[0].defUp == 4);
    assert(powerUpTypes.items[1].defUp == 8);
    assert(powerUpTypes.items[2].defUp == 10);
    assert(powerUpTypes.items[3].defUp == 70);

    assert(powerUps.items[0].typeId == 0);
    assert(powerUps.items[1].typeId == 3);
    assert(powerUps.items[2].typeId == 2);

    assert(PowerUpArray_searchLocation(&powerUps, Location_make(Point_make(2, 3), 0)) == 2);
    assert(PowerUpArray_searchLocation(&powerUps, Location_make(Point_make(1, 2), 3)) == 0);
    assert(PowerUpArray_searchLocation(&powerUps, Location_make(Point_make(2, 1), 0)) == 1);

    Player player;
    player.hp = 1;
    player.exp = 2;
    player.str = 3;
    player.def = 4;
    PowerUp_use(&powerUpTypes, &(powerUps.items[1]), &player);
    assert(player.hp == 6);
    assert(player.exp == 8);
    assert(player.str == 10);
    assert(player.def == 12);

    PowerUpArray_deallocate(&powerUps);
    PowerUpTypeArray_deallocate(&powerUpTypes);
    
    printf("  PowerUp tested.\n");
}