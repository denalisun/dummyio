#include "raylib.h"
#include "game/player.h"
#include "game/zombie.h"
#include "game/world.h"
#include "game/ui.h"
#include "game/gun.h"
#include "game/projectile.h"
#include "structs/array.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <limits.h>

int main()
{
    InitWindow(1280, 720, "DUMMY");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    int screenWidth, screenHeight = GetScreenWidth(), GetScreenHeight();
    
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
    GameWorld* world = ConstructWorld(baseWorldMap);

    Camera2D camera = { 0 };
    camera.rotation = 0;
    camera.zoom = 1.0f;

    Player* localPlayer = ConstructPlayer(200, 100, 100, 100, world, &camera);
    WorldSetPlayer(world, localPlayer);

    Gun* testGun = ConstructGun("TestGun", 0.05, 10, 10, 10, INT_MAX, INT_MAX, FIREMODE_AUTO);
    GiveGun(localPlayer, testGun);

    while (!WindowShouldClose()) {
        // Getting screen size
        screenWidth = GetScreenWidth();
        screenHeight = GetScreenHeight();

        // Updating objects
        for (int i = 0; i < ZOMBIE_COUNT; i++)
        {
            Zombie* zm = world->AllZombies[i];
            if (zm != 0)
            {
                UpdateZombie(zm, localPlayer);
                if (zm->health <= 0) world->AllZombies[i] = 0;
            }
        }

        UpdatePlayer(localPlayer);

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
        BeginMode2D(camera);

        WorldRenderMap(world);
        
        DrawPlayer(localPlayer);
        for (int i = 0; i < ZOMBIE_COUNT; i++) {
            if (world->AllZombies[i] != 0) DrawZombie(world->AllZombies[i]);
        }

        WorldRenderProjectiles(world);

        EndMode2D();
        DrawUI(world);
        EndDrawing();
    }

    ArrayFree(&world->AllProjectiles);
    free(world->AllZombies);
    free(localPlayer);

    CloseWindow();
    
    return 0;
}