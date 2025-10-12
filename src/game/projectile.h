#ifndef PROJECTILE_H
#define PROJECTILE_H

#define PROJECTILE_LIFETIME 1.0f

#include "gun.h"
#include "world.h"

struct Player;

typedef struct Projectile
{
    GameWorld* world;
    Gun* gunRef;
    struct Player* plrRef;
    float rotation;
    float x;
    float y;
    float lifeTime;
} Projectile;

Projectile* ConstructProjectile(GameWorld* world, Gun* gun, struct Player* plr, float rotation);
void UpdateProjectile(Projectile *proj);
void RenderProjectile(Projectile *proj);

#endif