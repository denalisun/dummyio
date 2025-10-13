#include "zombie.h"
#include "world.h"
#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

Zombie* ConstructZombie(float x, float y, float health, float maxHealth, GameWorld* world)
{
    Zombie* zm = malloc(sizeof(Zombie));
    zm->x = x;
    zm->y = y;
    zm->rotation = 0;
    zm->health = health;
    zm->maxHealth = maxHealth;
    zm->world = world;
    return zm;
}

void UpdateZombie(Zombie *zm, Player *plr)
{
    zm->rotation = atan2(zm->y - plr->y, zm->x - plr->x);
    float x = zm->x - cos(zm->rotation) * ((float)100 * GetFrameTime());
    float y = zm->y - sin(zm->rotation) * ((float)100 * GetFrameTime());

    for (int i = 0; i < ZOMBIE_COUNT; i++)
    {
        if (zm->world->AllZombies[i] == NULL || zm->world->AllZombies[i] == zm)
            continue;
        Zombie* them = zm->world->AllZombies[i];
        
        Rectangle ourRec = { 0 };
        ourRec.x = x;
        ourRec.y = y;
        ourRec.width = 40;
        ourRec.height = 40;

        Rectangle theirRec = { 0 };
        theirRec.x = them->x;
        theirRec.y = them->y;
        theirRec.width = 40;
        theirRec.height = 40;

        if (CheckCollisionRecs(ourRec, theirRec)) {
            float dx = x - them->x;
            float dy = y - them->y;
            float dist = sqrt(dx*dx + dy*dy);
            if (dist > 0.001f) {
                x += (dx / dist) * 1.0f;
                y += (dy / dist) * 1.0f;
            }
        }
    }

    // zm->x = x;
    // zm->y = y;
    if (!is_blocked(zm->world, x, zm->y)) zm->x = x;
    if (!is_blocked(zm->world, zm->x, y)) zm->y = y;
}

void DrawZombie(Zombie *zm)
{
    DrawRectanglePro(
        (Rectangle){zm->x, zm->y, 40, 40},
        (Vector2){20, 20},
        zm->rotation * RAD2DEG,
        GREEN);
}