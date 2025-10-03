#include "world.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "raylib.h"
#include <math.h>

GameWorld* ConstructWorld(int WorldMap[18][32]) {
    GameWorld* p = malloc(sizeof(GameWorld));
    p->CurrentWave = 0;
    p->AllZombies = calloc(ZOMBIE_COUNT, sizeof(Zombie*));
    p->LocalPlayer = 0;
    memcpy(p->WorldMap, WorldMap, sizeof(int[18][32]));
    return p;
}

void WorldSetPlayer(GameWorld* world, Player* plr) {
    world->LocalPlayer = plr;
}

void WorldAddZombie(GameWorld* world, float x, float y) {
    for (int i = 0; i < ZOMBIE_COUNT; i++) {
        if (world->AllZombies[i] == 0) {
            world->AllZombies[i] = ConstructZombie(
                x, 
                y, 
                100 * world->CurrentWave,
                100 * world->CurrentWave
            );
            break;
        }
    }
}

void WorldRenderMap(GameWorld* world) {
    for (int i = 0; i < (sizeof(world->WorldMap) / sizeof(world->WorldMap[0])); i++) {
        for (int j = 0; j < (sizeof(world->WorldMap[i]) / sizeof(world->WorldMap[i][0])); j++) {
            if (world->WorldMap[i][j] == 1) DrawRectangle(j * 40, i * 40, 40, 40, GRAY);
        }
    }
}

// void WorldSetWave(GameWorld* world);