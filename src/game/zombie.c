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
    zm->hitBox = (Rectangle){zm->x, zm->y, 50, 50};
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

        if (CheckCollisionRecs(zm->hitBox, them->hitBox)) {
            float dx = x - them->x;
            float dy = y - them->y;
            float dist = sqrt(dx*dx + dy*dy);
            if (dist > 0.001f) {
                x += (dx / dist) * 1.0f;
                y += (dy / dist) * 1.0f;
            }
        }
    }

    zm->hitBox.x = zm->x - 25;
    zm->hitBox.y = zm->y - 25;

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
    DrawRectangleLines(zm->hitBox.x, zm->hitBox.y, zm->hitBox.width, zm->hitBox.height, RED);
}