#ifndef PROJECTILE_H
#define PROJECTILE_H

#define PROJECTILE_LIFETIME 1.0f

#include "gun.h"

struct Player;
struct GameWorld;

typedef struct Projectile
{
    struct GameWorld* world;
    Gun* gunRef;
    struct Player* plrRef;
    float rotation;
    float x;
    float y;
    float lifeTime;
} Projectile;

Projectile* ConstructProjectile(Gun* gun, struct Player* plr, float rotation);
void UpdateProjectile(Projectile *proj);
void RenderProjectile(Projectile *proj);

#endif