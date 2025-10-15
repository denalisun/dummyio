#include "projectile.h"
#include "player.h"
#include "raylib.h"
#include "world.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

Projectile* ConstructProjectile(Gun* gun, Player* plr, float rotation)
{
    Projectile* p = malloc(sizeof(Projectile));
    p->world = plr->world;
    p->gunRef = gun;
    p->plrRef = plr;
    p->rotation = rotation;
    p->x = plr->x;
    p->y = plr->y;
    p->lifeTime = 0.0f;
    return p;
}

// I gotta fix whatever is wrong with the multiple bullet damage bug
void UpdateProjectile(Projectile *proj)
{
    proj->x += (cos(proj->rotation)) * (2500.f * GetFrameTime());
    proj->y += (sin(proj->rotation)) * (2500.f * GetFrameTime());

    Rectangle thisRect = { 0 };
    thisRect.x = proj->x;
    thisRect.y = proj->y;
    thisRect.width = 10;
    thisRect.height = 10;

    for (int i = 0; i < ZOMBIE_COUNT; i++)
    {
        if (proj->world->AllZombies[i] == NULL) continue;
        Zombie* zm = proj->world->AllZombies[i];
        Rectangle zmRect = { 0 };
        zmRect.x = zm->x;
        zmRect.y = zm->y;
        zmRect.width = 40;
        zmRect.height = 40;
        if (CheckCollisionRecs(zmRect, thisRect))
        {
            zm->health -= 10.0f;
            printf("hp: %f\n", zm->health);
            proj->lifeTime = PROJECTILE_LIFETIME;
        }
    }

    proj->lifeTime += GetFrameTime();
}

void RenderProjectile(Projectile *proj)
{
    DrawRectangle(proj->x, proj->y, 10, 10, YELLOW);
    // printf("x: %f, y: %f\n", proj->x, proj->y);
}