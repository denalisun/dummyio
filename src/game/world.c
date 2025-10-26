#include "world.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "raylib.h"

GameWorld* ConstructWorld(int WorldMap[18][32])
{
    GameWorld* p = malloc(sizeof(GameWorld));
    p->CurrentWave = 0;
    p->AllZombies = calloc(ZOMBIE_COUNT, sizeof(Zombie *));
    ConstructArray(&p->AllProjectiles, 1);
    p->LocalPlayer = 0;
    p->ZombiesSpawned = 0;
    p->ZombiesToSpawn = 0;
    p->WaveTimer = -1;
    p->CurrentWaveState = WAVE_ACTIVE;
    memcpy(p->WorldMap, WorldMap, sizeof(int[18][32]));
    return p;
}

void WorldSetPlayer(GameWorld* world, Player* plr)
{
    world->LocalPlayer = plr;
}

void WorldAddZombie(GameWorld* world, float x, float y)
{
    for (int i = 0; i < ZOMBIE_COUNT; i++) {
        if (world->AllZombies[i] == 0) {
            float health = 100.0f + (25.0f * (float)(world->CurrentWave - 1));
            world->AllZombies[i] = ConstructZombie(
                x,
                y,
                health,
                health,
                world
            );
            break;
        }
    }
}

void WorldRenderMap(GameWorld* world)
{
    for (int i = 0; i < (sizeof(world->WorldMap) / sizeof(world->WorldMap[0])); i++) {
        for (int j = 0; j < (sizeof(world->WorldMap[i]) / sizeof(world->WorldMap[i][0])); j++) {
            if (world->WorldMap[i][j] == 1) DrawRectangle(j * 40, i * 40, 40, 40, GRAY);
        }
    }
}

void WorldSpawnProjectile(GameWorld* world, Gun* gun, struct Player* plr, float rotation)
{
    Projectile* proj = ConstructProjectile(gun, plr, rotation);
    ArrayInsert(&world->AllProjectiles, (uintptr_t)proj);
}

void WorldUpdateProjectiles(GameWorld* world)
{
    for (size_t i = 0; i < world->AllProjectiles.used; i++)
    {
        Projectile* proj = (Projectile*)ArrayGet(&world->AllProjectiles, i);
        if (proj == NULL) continue;
        UpdateProjectile(proj);
        
        if (proj->lifeTime >= PROJECTILE_LIFETIME)
        {
            ArrayRemove(&world->AllProjectiles, (int)i);
            i--;
        }
    }
}

void WorldRenderProjectiles(GameWorld* world)
{
    for (size_t i = 0; i < world->AllProjectiles.used; i++)
    {
        Projectile* proj = (Projectile*)world->AllProjectiles.array[i];
        if (proj == 0) continue;
        RenderProjectile(proj);
    }
}

void WorldStartWave(GameWorld* world)
{
    world->CurrentWave++;
    world->CurrentWaveState = WAVE_ACTIVE;

    world->ZombiesSpawned = 0;
    world->ZombiesToSpawn = (4 + world->CurrentWave) > ZOMBIE_COUNT ? ZOMBIE_COUNT : (4 + world->CurrentWave);

    int zmToSpawnFor = world->ZombiesToSpawn;
    for (int i = 0; i < zmToSpawnFor; i++)
    {
        WorldAddZombie(world, 100, 100);
        world->ZombiesSpawned++;
        world->ZombiesToSpawn--;
    }
}

void WorldEndWave(GameWorld* world)
{
    world->CurrentWaveState = WAVE_CHANGING;
    world->WaveTimer = 5.0f;

    // Reset all zombies
    for (int i = 0; i < ZOMBIE_COUNT; i++)
    {
        world->AllZombies[i] = NULL;
    }

    printf("Wave ended!\n");
}

void WorldWaveLogic(GameWorld* world)
{
    switch (world->CurrentWaveState)
    {
    case WAVE_ACTIVE:
        if (GetAliveZombies(world) == 0) WorldEndWave(world);
        break;

    case WAVE_CHANGING:
        world->WaveTimer -= GetFrameTime();
        if (world->WaveTimer <= 0.0f) WorldStartWave(world);
        break;
    
    default:
        break;
    }
}

int GetAliveZombies(GameWorld* world)
{
    int zm = 0;
    for (int i = 0; i < ZOMBIE_COUNT; i++)
    {
        if (world->AllZombies[i] == 0) continue;
        zm++;
    }
    return zm;
}

bool is_blocked(GameWorld* world, float x, float y)
{
    int tileX = (int)(x / 40);
    int tileY = (int)(y / 40);

    return world->WorldMap[tileY][tileX] == 1;
}
