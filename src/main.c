#include "raylib.h"
#include "game/player.h"
#include "game/zombie.h"
#include "game/ui.h"
#include "game/world.h"
#include "game/gun.h"
#include "structs/array.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <limits.h>

int main()
{
    InitWindow(1280, 720, "DUMMY");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    
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
    UI* localUi = ConstructUI(world);
    world->LocalUI = localUi;

    Camera2D camera = { 0 };
    camera.rotation = 0;
    camera.zoom = 1.0f;

    Player* localPlayer = ConstructPlayer(200, 100, 100, 100, world, &camera);
    WorldSetPlayer(world, localPlayer);

    Gun* testGun = ConstructGun("TestGun", 0.01, 10, 10, 10, INT_MAX, INT_MAX, 2.0f, FIREMODE_SEMIAUTO);
    Gun* testAutoGun = ConstructGun("TestAutomatic", 0.025, 25, 30, 30, 180, 180, 3.0f, FIREMODE_AUTO);
    GiveGun(localPlayer, testGun);
    GiveGun(localPlayer, testAutoGun);

    while (!WindowShouldClose()) {
        // Updating stuff
        UpdateUI(localUi);

        for (int i = 0; i < ZOMBIE_COUNT; i++)
        {
            if (world->AllZombies[i] != 0)
            {
                Zombie* zm = world->AllZombies[i];
                UpdateZombie(zm, localPlayer);
                if (zm->health <= 0) world->AllZombies[i] = NULL;
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
        DrawUI(localUi);
        EndDrawing();
    }

    ArrayFree(&world->AllProjectiles);
    free(world->AllZombies);
    free(localPlayer);

    CloseWindow();
    
    return 0;
}
