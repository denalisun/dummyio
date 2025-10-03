#include "raylib.h"
#include "game/player.h"
#include "game/zombie.h"
#include <stdlib.h>
#include <stdio.h>

#define ZOMBIE_COUNT 24

int main(void)
{
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Dummy");

    Player* localPlayer = ConstructPlayer(100, 100, 100, 100);
    
    Zombie allZombies[ZOMBIE_COUNT];
    // if (!allZombies) return -1;
    allZombies[0] = *ConstructZombie(300, 300, 100, 100);

    while (!WindowShouldClose()) {
        // Updating objects
        UpdatePlayer(localPlayer);
        // for (int i = 0; i < ZOMBIE_COUNT; i++) {
        //     Zombie* zm = allZombies[i];
        //     UpdateZombie(zm, localPlayer);
        // }
        
        // Rendering
        BeginDrawing();
        ClearBackground(BLACK);
        DrawFPS(10, screenHeight - 30);

        DrawPlayer(localPlayer);
        for (int i = 0; i < ZOMBIE_COUNT; i++) {
            DrawZombie(&allZombies[i]);
        }

        EndDrawing();
    }

    //free(allZombies);
    free(localPlayer);

    CloseWindow();
    
    return 0;
}