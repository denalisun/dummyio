#include "raylib.h"
#include "game/player.h"
#include "game/zombie.h"
#include "game/ui.h"
#include "game/world.h"
#include "game/gun.h"
#include "game/state.h"
#include "game/game.h"
#include <stdint.h>
#include <stdio.h>
#include <limits.h>
#include "data/fonts.h"

//#define PLATFORM_WEB
#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

Game *game;
GameWorld *world;
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

const Color unselectedColor = (Color){46, 65, 102, 255};
const Color selectedColor = (Color){75, 120, 166, 255};

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
        
        // Options
        char playButtonText[] = "PLAY";
        Vector2 playButtonMeasurement = MeasureTextEx(MAIN_FONT, playButtonText, 72, 2);
        Rectangle playButtonBox = (Rectangle){
            .x = 20,
            .y = 250,
            .width = playButtonMeasurement.x + 32,
            .height = playButtonMeasurement.y,
        };
        bool bIsPlayButtonSelected = CheckCollisionPointRec(GetMousePosition(), playButtonBox);
        DrawTextEx(MAIN_FONT, playButtonText, (Vector2){ playButtonBox.x, playButtonBox.y }, 72, 2, bIsPlayButtonSelected ? selectedColor : unselectedColor);

        // This is for debug
        DrawRectangleLinesEx(playButtonBox, 2, WHITE);

        char optionsButtonText[] = "OPTIONS";
        Vector2 optionsButtonMeasurement = MeasureTextEx(MAIN_FONT, optionsButtonText, 72, 2);
        Rectangle optionsButtonBox = (Rectangle){
            .x = 20,
            .y = 300,
            .width = optionsButtonMeasurement.x + 32,
            .height = optionsButtonMeasurement.y,
        };
        bool bIsOptionsButtonSelected = CheckCollisionPointRec(GetMousePosition(), optionsButtonBox);
        DrawTextEx(MAIN_FONT, optionsButtonText, (Vector2){ optionsButtonBox.x, optionsButtonBox.y }, 72, 2, bIsOptionsButtonSelected ? selectedColor : unselectedColor);

        // This is for debug
        DrawRectangleLinesEx(optionsButtonBox, 2, WHITE);

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
        if (world == NULL)
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
            world = ConstructWorld(game, baseWorldMap);
            world->LocalUI = ConstructUI(world, MAIN_FONT);
            
            Camera2D camera = (Camera2D){ 
                .offset = (Vector2){ 0.0f, 0.0f },
                .rotation = 0,
                .zoom = 1.0f,
                .target = (Vector2){ 0.0f, 0.0f },
            };
            camera.rotation = 0;
            camera.zoom = 1.0f;

            world->LocalPlayer = ConstructPlayer(200, 100, 100, 100, world, &camera);
            
            // Gun* testGun = ConstructGun("TestGun", 0.01, 10, 10, 10, INT_MAX, INT_MAX, 2.0f, FIREMODE_SEMIAUTO);
            // Gun* testAutoGun = ConstructGun("TestAutomatic", 0.025, 25, 30, 30, 180, 180, 3.0f, FIREMODE_AUTO);
            // GiveGun(localPlayer, testGun);
            // GiveGun(localPlayer, testAutoGun);

            Gun* machineGun = ConstructGun("MG-42", 0.025, 10, 120, 120, 480, 480, 3.0f, FIREMODE_AUTO);
            GiveGun(world->LocalPlayer, machineGun);
        }

        UpdateUI(world->LocalUI);

        if (!world->bIsPaused)
        {
            for (int i = 0; i < ZOMBIE_COUNT; i++)
            {
                if (world->AllZombies[i] != 0)
                {
                    Zombie* zm = world->AllZombies[i];
                    UpdateZombie(zm, world->LocalPlayer);
                    if (zm->health <= 0) world->AllZombies[i] = NULL;
                }
            }

            UpdatePlayer(world->LocalPlayer);

            WorldUpdateProjectiles(world);

            if (IsKeyPressed(KEY_F))
            {
                for (int i = 0; i < ZOMBIE_COUNT; i++)
                {
                    if (world->AllZombies[i] == 0) continue;
                    world->AllZombies[i] = 0;
                }
            }

            // Wave logic
            WorldWaveLogic(world);
        }

        // Rendering
        BeginDrawing();
        ClearBackground(BLACK);
        BeginMode2D(*world->LocalPlayer->camera);

        WorldRenderMap(world);
        
        DrawPlayer(world->LocalPlayer);
        for (int i = 0; i < ZOMBIE_COUNT; i++) {
            if (world->AllZombies[i] != 0) DrawZombie(world->AllZombies[i]);
        }

        WorldRenderProjectiles(world);

        EndMode2D();
        DrawUI(world->LocalUI);

        EndDrawing();
    }
}
