#include <stdio.h>
#include <math.h>
#include <string.h>
#include "world.h"
#include "ui.h"
#include "raylib.h"

UI* ConstructUI(GameWorld* world)
{
    UI* ui = malloc(sizeof(UI));
    ui->bConsoleEnabled = false;
    strcpy(ui->cmdBuf, "\0");
    ui->cmdBufLetterCount = 0;
    ui->world = world;
    return ui;
}

void UpdateUI(UI* ui)
{
    if (IsKeyPressed(KEY_GRAVE))
    {
        ui->bConsoleEnabled = !ui->bConsoleEnabled;
    }

    if (ui->bConsoleEnabled)
    {
        int key = GetCharPressed();
        while (key > 0)
        {
            if ((key >= 32) && (key <= 125) && (ui->cmdBufLetterCount < 255))
            {
                ui->cmdBuf[ui->cmdBufLetterCount] = (char)key;
                ui->cmdBuf[ui->cmdBufLetterCount+1] = '\0';
                ui->cmdBufLetterCount++;
            }

            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE))
        {
            ui->cmdBufLetterCount--;
            if (ui->cmdBufLetterCount < 0) ui->cmdBufLetterCount = 0;
            ui->cmdBuf[ui->cmdBufLetterCount] = '\0';
        }
    }
}

#define DRAW_FPS

void DrawUI(UI* ui)
{
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    // Draw zombies left
    char zombiesBuffer[16];
    sprintf(zombiesBuffer, "%d Zombies Left", GetAliveZombies(ui->world));
    DrawText(zombiesBuffer, 10, 10, 34, DARKGREEN);

    // Draw Round Number
    char roundBuffer[10];
    sprintf(roundBuffer, "%d", ui->world->CurrentWave);
    Color roundColor = { 0 };
    roundColor.r = 255.0f * (ui->world->WaveTimer - ((int)floorf(ui->world->WaveTimer)));
    roundColor.g = 255.0f * (ui->world->WaveTimer - ((int)floorf(ui->world->WaveTimer)));
    roundColor.b = 255.0f * (ui->world->WaveTimer - ((int)floorf(ui->world->WaveTimer)));
    roundColor.a = 144.0f;
    DrawText(roundBuffer, 10, screenHeight - 82, 72, ui->world->CurrentWaveState == WAVE_ACTIVE ? RED : roundColor);

    // Draw money
    char moneyBuffer[7];
    sprintf(moneyBuffer, "$%d", ui->world->LocalPlayer->money);
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
    Gun* gun = ui->world->LocalPlayer->AllGuns[ui->world->LocalPlayer->EquippedGun];
    DrawText(gun->name, screenWidth - MeasureText(gun->name, 24), screenHeight - 24, 24, WHITE);

    // Draw ammo
    char ammoText[32];
    sprintf(ammoText, "%d / %d", gun->ammo, gun->reserveAmmo);
    DrawText(ammoText, screenWidth - MeasureText(ammoText, 18), screenHeight - 48, 18, WHITE);

    // Draw reloading text
    if (gun->reloadingTimer > 0.0f)
    {
        char reloadingText[13] = "Reloading...";
        DrawText("Reloading...", (screenWidth / 2) - (MeasureText(reloadingText, 18) / 2), screenHeight - 48, 18, GRAY);
    }

    // Draw redscreen
    Color redscreenColor = { 0 };
    redscreenColor.r = 255.0f;
    redscreenColor.g = 0.0f;
    redscreenColor.b = 0.0f;
    redscreenColor.a = 255.0f - ((ui->world->LocalPlayer->health / ui->world->LocalPlayer->maxHealth) * 255);
    DrawRectangle(0, 0, screenWidth, screenHeight, redscreenColor);

    // Draw Console
    if (ui->bConsoleEnabled)
    {
        DrawRectangle(0, screenHeight - 17, screenWidth, 17, DARKGRAY);
        DrawRectangleLines(0, screenHeight - 17, screenWidth, 17, WHITE);
        DrawText(ui->cmdBuf, 2, screenHeight - 12, 12, WHITE);
    }

    // Draw FPS
#ifdef DRAW_FPS
    char fpsStr[16];
    sprintf(fpsStr, "%d FPS", GetFPS());
    DrawText(fpsStr, screenWidth - (strlen(fpsStr) * 24), 24, 24, GREEN);
#endif
}