#include <assert.h>
#include <stdio.h>
#include "../src/powerup.h"
#include "../src/stringutils.h"

void testPowerup() {
    Powerup power;
    printf("  Testing Powerup...\n");

    FILE *fin = fopen("./test/powerup.in", "r");
    assert(fin != NULL);

    Powerup_load(&power,fin);
    assert(power.length == 3);
    assert(StringUtils_strcmpi(power.items[0].powerName, "HP_Up") == 0);
    //assert(power.items[0] == 0);
    //assert(StringUtils_strcmpi(power.items[0].powerName, "HP_Up") == 0);
    printf("  Powerup tested.\n");
}