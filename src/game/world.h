#ifndef WORLD_H
#define WORLD_H

#define ZOMBIE_COUNT 24

#include "player.h"
#include "zombie.h"

typedef struct {
    Player* LocalPlayer;
    Zombie** AllZombies;
    int WorldMap[18][32];
    int CurrentWave;
} GameWorld;

GameWorld* ConstructWorld(int WorldMap[18][32]);
void WorldSetPlayer(GameWorld* world, Player* plr);
void WorldAddZombie(GameWorld* world, float x, float y);
void WorldRenderMap(GameWorld* world);
// void WorldSetWave(GameWorld* world);

#endif