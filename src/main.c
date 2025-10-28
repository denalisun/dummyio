#include "raylib.h"
#include "game/player.h"
#include "game/zombie.h"
#include "game/ui.h"
#include "game/world.h"
#include "game/gun.h"
#include "game/state.h"
#include <stdint.h>
#include <stdio.h>
#include <limits.h>
#include "data/fonts.h"

//#define PLATFORM_WEB
#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

GameState gameState;
GameWorld *world;
Font MAIN_FONT;

void UpdateGameLoop(void); // This is for web programming

int main()
{
    // MAIN_FONT = LoadFontEx("assets/fonts/bytesized.ttf", 32, 0, 250);
    InitWindow(1280, 720, "DUMMY");
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    // MAIN_FONT = LoadFont("assets/fonts/bytesized.ttf");
    MAIN_FONT = LoadFontEx("assets/fonts/bytesized.ttf", 1024, 0, 250);

    gameState = STATE_MAINMENU;

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

void UpdateGameLoop(void)
{
    // Updating stuff
    if (gameState == STATE_MAINMENU)
    {
        BeginDrawing();
        ClearBackground((Color){
            .r = 76.0f,
            .g = 22.0f,
            .b = 22.0f,
            .a = 255.0f
        });

        // Color textColor = (Color){ 105, 105, 105, 255 };

        int screenWidth = GetScreenWidth();
        int screenHeight = GetScreenHeight();

        char titleText[] = "DUMMY";
        DrawTextEx(MAIN_FONT, titleText, (Vector2){(screenWidth / 2) - (MeasureTextEx(MAIN_FONT, titleText, 92, 2).x / 2), 0}, 92, 2, WHITE);
        // DrawText("created by denalisun (c) 2025", 10, screenHeight - 10 - 24, 24, WHITE);
        DrawTextEx(MAIN_FONT, "created by denalisun (c) 2025", (Vector2){10, screenHeight - MeasureTextEx(MAIN_FONT, "created by denalisun (c) 2025", 36, 2).y}, 36, 2, WHITE);

        if (IsKeyPressed(KEY_ENTER))
        {
            gameState = STATE_INGAME;
        }

        EndDrawing();
    }
    else if (gameState == STATE_INGAME)
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
            world = ConstructWorld(baseWorldMap);
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
