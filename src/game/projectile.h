#ifndef PROJECTILE_H
#define PROJECTILE_H

// #define PROJECTILE_LIFETIME 1.0f
#define PROJECTILE_LIFETIME 50.0f

#include "gun.h"
#include "raylib.h"

struct Player;
struct GameWorld;

typedef struct Projectile
{
    struct GameWorld* world;
    Gun* gunRef;
    struct Player* plrRef;
    float rotation;
    Rectangle hitBox;
    float x;
    float y;
    float lifeTime;
} Projectile;

Projectile* ConstructProjectile(Gun* gun, struct Player* plr, float rotation);
void UpdateProjectile(Projectile *proj);
void RenderProjectile(Projectile *proj);

#endif