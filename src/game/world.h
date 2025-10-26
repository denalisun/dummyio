#ifndef WORLD_H
#define WORLD_H

#define ZOMBIE_COUNT 16
#define IN_BETWEEN_WAVE_TIME 5

#include "player.h"
#include "zombie.h"
#include "ui.h"
#include "state.h"
#include "projectile.h"
#include "../structs/array.h"

typedef enum WaveState
{
    WAVE_ACTIVE,
    WAVE_CHANGING,
} WaveState;

typedef struct GameWorld
{
    Player* LocalPlayer;
    Zombie** AllZombies;
    Array AllProjectiles;
    int ZombiesSpawned;
    int ZombiesToSpawn;
    int WorldMap[18][32];
    int CurrentWave;
    float WaveTimer;
    WaveState CurrentWaveState;
    UI* LocalUI;
} GameWorld;

GameWorld* ConstructWorld(int WorldMap[18][32]);
void WorldSetPlayer(GameWorld* world, Player* plr);
void WorldAddZombie(GameWorld* world, float x, float y);
void WorldRenderMap(GameWorld* world);

void WorldSpawnProjectile(GameWorld* world, Gun* gun, struct Player* plr, float rotation);
void WorldUpdateProjectiles(GameWorld* world);
void WorldRenderProjectiles(GameWorld* world);

void WorldStartWave(GameWorld* world);
void WorldEndWave(GameWorld* world);
void WorldWaveLogic(GameWorld* world);

int GetAliveZombies(GameWorld* world);

bool is_blocked(GameWorld* world, float x, float y);

#endif