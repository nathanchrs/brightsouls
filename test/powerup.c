#include <assert.h>
#include <stdio.h>
#include "../src/powerup.h"
#include "../src/stringutils.h"

void testPowerUp(const char *executableDirectory) {
    Powerup power;
    printf("  Testing Powerup...\n");

    FILE *fin = IO_openFile(executableDirectory, '../test/powerup.in');
    assert(fin != NULL);
    PowerUp_load(&power, fin);
    IO_closeFile(fin);

    assert(power.length == 3);
    assert(StringUtils_strcmpi(power.items[0].name, "HP_Up") == 0);
    //assert(power.items[0] == 0);
    //assert(StringUtils_strcmpi(power.items[0].powerName, "HP_Up") == 0);
    
    printf("  Powerup tested.\n");
}