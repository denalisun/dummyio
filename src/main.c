#include "raylib.h"
#include "game/player.h"
#include "game/zombie.h"
#include "game/ui.h"
#include "game/world.h"
#include "game/gun.h"
#include "game/state.h"
#include "structs/array.h"
#include "utils.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <limits.h>

//#define PLATFORM_WEB
#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

GameState gameState;
GameWorld *world;
// const char* splashText;

void UpdateGameLoop(void); // This is for web programming

int main()
{
    InitWindow(1280, 720, "DUMMY");
    SetWindowState(FLAG_WINDOW_RESIZABLE);

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

        int screenWidth = GetScreenWidth();

        char titleText[] = "DUMMY";
        DrawText(titleText, (screenWidth / 2) - (MeasureText(titleText, 48) / 2), 58, 48, WHITE);
        DrawText("Press Enter to Play!", (screenWidth / 2) - (MeasureText("Press Enter to Play!", 36) / 2), 56 + 36 + 10, 36, LIGHTGRAY);

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
            world->LocalUI = ConstructUI(world);
            
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
