#include <stdio.h>
#include <math.h>
#include <string.h>
#include "world.h"
#include "ui.h"
#include "raylib.h"

UI* ConstructUI(GameWorld* world, Font mainFont)
{
    UI* ui = malloc(sizeof(UI));
    ui->bConsoleEnabled = false;
    strcpy(ui->cmdBuf, "\0");
    ui->cmdBufLetterCount = 0;
    ui->world = world;
    ui->mainFont = mainFont;
    return ui;
}

void UpdateUI(UI* ui)
{
    if (IsKeyPressed(KEY_GRAVE))
    {
        ui->bConsoleEnabled = !ui->bConsoleEnabled;
    }

    if (IsKeyPressed(KEY_ESCAPE))
    {
        ui->world->bIsPaused = !ui->world->bIsPaused;
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

        if (IsKeyPressed(KEY_ENTER))
        {
            ui->cmdBufLetterCount = 0;
            memset(ui->cmdBuf, '\0', sizeof(char) * 256);
            ui->bConsoleEnabled = false;
        }
    }
}

// #define DRAW_FPS

void DrawUI(UI* ui)
{
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    float hudBounds = 0.0f;
    
    Vector2 textMeasure;
    
    // Draw zombies left
    char zombiesBuffer[16];
    sprintf(zombiesBuffer, "%d Zombies Left", GetAliveZombies(ui->world));
    // DrawText(zombiesBuffer, 10, 10, 34, DARKGREEN);
    DrawTextEx(ui->mainFont, zombiesBuffer, (Vector2){10 + hudBounds, -10 + hudBounds}, 68, 2, DARKGREEN);

    // Draw Round Number
    char roundBuffer[10];
    sprintf(roundBuffer, "%d", ui->world->CurrentWave);
    Color roundColor = { 0 };
    roundColor.r = 255.0f * (ui->world->WaveTimer - ((int)floorf(ui->world->WaveTimer)));
    roundColor.g = 255.0f * (ui->world->WaveTimer - ((int)floorf(ui->world->WaveTimer)));
    roundColor.b = 255.0f * (ui->world->WaveTimer - ((int)floorf(ui->world->WaveTimer)));
    roundColor.a = 144.0f;
    // DrawText(roundBuffer, 10, screenHeight - 82, 72, ui->world->CurrentWaveState == WAVE_ACTIVE ? RED : roundColor);
    textMeasure = MeasureTextEx(ui->mainFont, roundBuffer, 144, 2);
    DrawTextEx(ui->mainFont, roundBuffer, (Vector2){10 + hudBounds, (screenHeight - textMeasure.y + 32) - hudBounds}, 144, 2, ui->world->CurrentWaveState == WAVE_ACTIVE ? RED : roundColor);

    // Draw money
    char moneyBuffer[7];
    sprintf(moneyBuffer, "$%d", ui->world->LocalPlayer->money);
    // DrawText(moneyBuffer, 10, screenHeight - 140, 48, WHITE);
    textMeasure = MeasureTextEx(ui->mainFont, moneyBuffer, 48, 2);
    DrawTextEx(ui->mainFont, moneyBuffer, (Vector2){ 10 + hudBounds, (screenHeight - textMeasure.y - 84) - hudBounds}, 48, 2, WHITE);

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
    // DrawText(gun->name, screenWidth - MeasureText(gun->name, 24), screenHeight - 24, 24, WHITE);
    textMeasure = MeasureTextEx(ui->mainFont, gun->name, 84, 2);
    DrawTextEx(ui->mainFont, gun->name, (Vector2){ (screenWidth - textMeasure.x) - hudBounds, (screenHeight - 84) - hudBounds }, 84, 2, WHITE);

    // Draw ammo
    char ammoText[32];
    sprintf(ammoText, "%d / %d", gun->ammo, gun->reserveAmmo);
    // DrawText(ammoText, screenWidth - MeasureText(ammoText, 18), screenHeight - 48, 18, WHITE);
    textMeasure = MeasureTextEx(ui->mainFont, ammoText, 48, 2);
    DrawTextEx(ui->mainFont, ammoText, (Vector2){ (screenWidth - textMeasure.x) - hudBounds, (screenHeight - textMeasure.y - 60) - hudBounds }, 48, 2, WHITE);

    // Draw reloading text
    if (gun->reloadingTimer > 0.0f)
    {
        char reloadingText[13] = "Reloading...";
        // DrawText("Reloading...", (screenWidth / 2) - (MeasureText(reloadingText, 18) / 2), screenHeight - 48, 18, GRAY);
        textMeasure = MeasureTextEx(ui->mainFont, reloadingText, 32, 2);
        DrawTextEx(ui->mainFont, reloadingText, (Vector2){ (screenWidth / 2) - (textMeasure.x / 2), screenHeight - 48 }, 32, 2, LIGHTGRAY);
    }

    // Draw redscreen
    Color redscreenColor = { 0 };
    redscreenColor.r = 255.0f;
    redscreenColor.g = 0.0f;
    redscreenColor.b = 0.0f;
    redscreenColor.a = 255.0f - ((ui->world->LocalPlayer->health / ui->world->LocalPlayer->maxHealth) * 255);
    DrawRectangle(0, 0, screenWidth, screenHeight, redscreenColor);

    if (ui->world->bIsPaused)
    {
        char pausedText[] = "PAUSED";
        DrawRectangle(0, 0, screenWidth, screenHeight, (Color){ 0, 0, 0, 178 });
        textMeasure = MeasureTextEx(ui->mainFont, pausedText, 36, 2);
        DrawTextEx(ui->mainFont, pausedText, (Vector2){ ((float)screenWidth / 2) - (textMeasure.x / 2), ((float)screenHeight / 2) - (textMeasure.y / 2) }, 36, 2, WHITE);
    }

    // Draw Console
    if (ui->bConsoleEnabled)
    {
        DrawRectangle(0, 0, screenWidth, 17, DARKGRAY);
        DrawRectangleLines(0, 0, screenWidth, 17, WHITE);
        DrawText(ui->cmdBuf, 2, 5, 12, WHITE);
    }

    // Draw FPS
#ifdef DRAW_FPS
    char fpsStr[16];
    sprintf(fpsStr, "%d FPS", GetFPS());
    DrawText(fpsStr, screenWidth - (strlen(fpsStr) * 24), 24, 24, GREEN);
#endif
}
