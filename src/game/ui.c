#include "ui.h"
#include <stdio.h>

void DrawUI(GameWorld* world)
{
    int screenHeight = GetScreenHeight();

    // Draw zombies left
    char zombiesBuffer[16];
    sprintf(zombiesBuffer, "%d Zombies Left", GetAliveZombies(world));
    DrawText(zombiesBuffer, 10, 10, 34, GREEN);

    // Draw Round Number
    char roundBuffer[10];
    sprintf(roundBuffer, "%d", world->CurrentWave);
    DrawText(roundBuffer, 10, screenHeight - 82, 72, RED);

    // Draw money
    char moneyBuffer[8];
    sprintf(moneyBuffer, "$ %d", world->LocalPlayer->money);
    DrawText(moneyBuffer, 10, screenHeight - 140, 48, WHITE);
}