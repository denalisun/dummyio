#include "raylib.h"
#include "game/player.h"
#include "game/zombie.h"
#include "game/ui.h"
#include "game/world.h"
#include "game/gun.h"
#include "game/state.h"
#include "game/game.h"
#include "game/menu.h"
#include <stdint.h>
#include <stdio.h>
#include <limits.h>
#include "data/fonts.h"

//#define PLATFORM_WEB
#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

Game *game;
Font MAIN_FONT;

void UpdateGameLoop(void); // This is for web programming

int main()
{
    // MAIN_FONT = LoadFontEx("assets/fonts/bytesized.ttf", 32, 0, 250);
    InitWindow(1280, 720, "DUMMY");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetExitKey(KEY_NULL);

    game = ConstructGame(STATE_MAINMENU, NULL);
    
    MAIN_FONT = LoadFontEx("assets/fonts/bytesized.ttf", 1024, 0, 250);
    game->mainFont = MAIN_FONT;

#ifdef PLATFORM_WEB
    emscripten_set_main_loop(UpdateGameLoop, 0, 1);
#else
    while (!WindowShouldClose()) {
        UpdateGameLoop();
    }
#endif

    CloseWindow();
    
    return 0;
}

const Color unselectedColor = {46, 65, 102, 255};
const Color selectedColor = {75, 120, 166, 255};

void UpdateGameLoop(void)
{
    // Updating stuff
    if (game->currentState == STATE_MAINMENU)
    {
        // Draw main menu
        BeginDrawing();
        ClearBackground((Color){11, 9, 20, 255});
        
        int screenWidth = GetScreenWidth();
        int screenHeight = GetScreenHeight();
        
        char titleText[] = "DUMMY";
        Vector2 titleTextMeasurement = MeasureTextEx(MAIN_FONT, titleText, 184, 2);
        DrawTextEx(MAIN_FONT, titleText, (Vector2){ screenWidth - titleTextMeasurement.x, 0 }, 184, 2, WHITE);
        DrawLineEx((Vector2){ screenWidth, titleTextMeasurement.y - 20 }, (Vector2){ (int)(screenWidth / 2), titleTextMeasurement.y - 20 }, 10, WHITE);

        char copyrightText[] = "created by denalisun (c) 2025";
        Vector2 copyrightMeasurement = MeasureTextEx(MAIN_FONT, copyrightText, 24, 2);
        DrawTextEx(MAIN_FONT, copyrightText, (Vector2){ 5, screenHeight - copyrightMeasurement.y }, 24, 2, WHITE);
        
        // Selections
        bool bIsPlayButtonSelected = RenderMenuButton(game, "PLAY", 72, (Vector2){ 20, 250 }, unselectedColor, selectedColor);
        bool bIsOptionsButtonSelected = RenderMenuButton(game, "OPTIONS", 72, (Vector2){ 20, 310 }, unselectedColor, selectedColor);

        if (bIsPlayButtonSelected && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            game->currentState = STATE_INGAME;
        }

        if (bIsOptionsButtonSelected && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            game->currentState = STATE_OPTIONSMENU;
        }

        EndDrawing();
    }
    else if (game->currentState == STATE_OPTIONSMENU)
    {
        BeginDrawing();
        ClearBackground((Color){ 11, 9, 20, 255 });

        int screenWidth = GetScreenWidth();
        //int screenHeight = GetScreenHeight();

        char optionsTitleText[] = "OPTIONS";
        Vector2 optionsTitleMeasurement = MeasureTextEx(MAIN_FONT, optionsTitleText, 184, 2);
        DrawTextEx(MAIN_FONT, optionsTitleText, (Vector2){ ((float)screenWidth / 2) - (optionsTitleMeasurement.x / 2), 0 }, 184, 2, WHITE);

        EndDrawing();
    }
    else if (game->currentState == STATE_INGAME)
    {
        if (game->world == NULL)
        {
            int baseWorldMap[18][32] = {
                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
            };
            game->world = ConstructWorld(game, baseWorldMap);
            game->world->LocalUI = ConstructUI(game->world, MAIN_FONT);
            
            Camera2D camera = (Camera2D){ 
                .offset = (Vector2){ 0.0f, 0.0f },
                .rotation = 0,
                .zoom = 1.0f,
                .target = (Vector2){ 0.0f, 0.0f },
            };
            camera.rotation = 0;
            camera.zoom = 1.0f;

            game->world->LocalPlayer = ConstructPlayer(200, 100, 100, 100, game->world, &camera);
            
            // Gun* testGun = ConstructGun("TestGun", 0.01, 10, 10, 10, INT_MAX, INT_MAX, 2.0f, FIREMODE_SEMIAUTO);
            // Gun* testAutoGun = ConstructGun("TestAutomatic", 0.025, 25, 30, 30, 180, 180, 3.0f, FIREMODE_AUTO);
            // GiveGun(localPlayer, testGun);
            // GiveGun(localPlayer, testAutoGun);

            Gun* machineGun = ConstructGun("MG-42", 0.025, 10, 120, 120, 480, 480, 3.0f, FIREMODE_AUTO);
            GiveGun(game->world->LocalPlayer, machineGun);
        }

        UpdateUI(game->world->LocalUI);

        if (!game->world->bIsPaused)
        {
            for (int i = 0; i < ZOMBIE_COUNT; i++)
            {
                if (game->world->AllZombies[i] != 0)
                {
                    Zombie* zm = game->world->AllZombies[i];
                    UpdateZombie(zm, game->world->LocalPlayer);
                    if (zm->health <= 0) game->world->AllZombies[i] = NULL;
                }
            }

            UpdatePlayer(game->world->LocalPlayer);

            WorldUpdateProjectiles(game->world);

            if (IsKeyPressed(KEY_F))
            {
                for (int i = 0; i < ZOMBIE_COUNT; i++)
                {
                    if (game->world->AllZombies[i] == 0) continue;
                    game->world->AllZombies[i] = 0;
                }
            }

            // Wave logic
            WorldWaveLogic(game->world);
        }

        // Rendering
        BeginDrawing();
        ClearBackground(BLACK);
        BeginMode2D(*game->world->LocalPlayer->camera);

        WorldRenderMap(game->world);
        
        DrawPlayer(game->world->LocalPlayer);
        for (int i = 0; i < ZOMBIE_COUNT; i++) {
            if (game->world->AllZombies[i] != 0) DrawZombie(game->world->AllZombies[i]);
        }

        WorldRenderProjectiles(game->world);

        EndMode2D();
        DrawUI(game->world->LocalUI);

        EndDrawing();
    }
}
