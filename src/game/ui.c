#include "ui.h"
#include <stdio.h>
#include <math.h>

void DrawUI(GameWorld* world)
{
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    // Draw zombies left
    char zombiesBuffer[16];
    sprintf(zombiesBuffer, "%d Zombies Left", GetAliveZombies(world));
    DrawText(zombiesBuffer, 10, 10, 34, DARKGREEN);

    // Draw Round Number
    char roundBuffer[10];
    sprintf(roundBuffer, "%d", world->CurrentWave);
    Color roundColor = { 0 };
    roundColor.r = 255.0f * (world->WaveTimer - ((int)floorf(world->WaveTimer)));
    roundColor.g = 255.0f * (world->WaveTimer - ((int)floorf(world->WaveTimer)));
    roundColor.b = 255.0f * (world->WaveTimer - ((int)floorf(world->WaveTimer)));
    roundColor.a = 144.0f;
    DrawText(roundBuffer, 10, screenHeight - 82, 72, world->CurrentWaveState == WAVE_ACTIVE ? RED : roundColor);

    // Draw money
    char moneyBuffer[7];
    sprintf(moneyBuffer, "$%d", world->LocalPlayer->money);
    DrawText(moneyBuffer, 10, screenHeight - 140, 48, WHITE);

    // Draw wave timer (I'm actually not doing this)
    // if (world->WaveTimer > 0.0f)
    // {
    //     char waveTimerBuffer[1];
    //     sprintf(waveTimerBuffer, "%d", (int)ceilf(world->WaveTimer));
    //     DrawText(waveTimerBuffer, screenWidth - 24, screenHeight - 24, 24, LIGHTGRAY);
    //     // I need to change this later
    // }

    // Draw gun
    Gun* gun = world->LocalPlayer->AllGuns[world->LocalPlayer->EquippedGun];
    DrawText(gun->name, screenWidth - (sizeof(gun->name) * 24), screenHeight - 24, 24, WHITE);

    // Draw redscreen
    Color redscreenColor = { 0 };
    redscreenColor.r = 255.0f;
    redscreenColor.g = 0.0f;
    redscreenColor.b = 0.0f;
    redscreenColor.a = 255.0f - ((world->LocalPlayer->health / world->LocalPlayer->maxHealth) * 255);
    DrawRectangle(0, 0, screenWidth, screenHeight, redscreenColor);
}