#include "player.h"
#include "world.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

Player* ConstructPlayer(float x, float y, float health, float maxHealth, GameWorld* world)
{
    Player* plr = malloc(sizeof(Player));
    plr->x = x;
    plr->y = y;
    plr->rotation = 0;
    plr->health = health;
    plr->maxHealth = maxHealth;
    plr->money = 500;
    plr->world = world;
    return plr;
}

void UpdatePlayer(Player *plr)
{
    float x = ((int)IsKeyDown(KEY_D) - (int)IsKeyDown(KEY_A)) * ((float)250 * GetFrameTime());
    float y = ((int)IsKeyDown(KEY_S) - (int)IsKeyDown(KEY_W)) * ((float)250 * GetFrameTime());
    
    const Vector2 mousePos = GetMousePosition();
    plr->rotation = atan2(mousePos.y - (GetScreenHeight() / 2.0f), mousePos.x - (GetScreenWidth() / 2.0f));

    // Normalizing (making sure it isnt faster diagonally)
    float length = sqrtf(x*x + y*y);
    if (length > 0)
    {
        x = ((x / length) * (250.0f * GetFrameTime())) + plr->x;
        y = ((y / length) * (250.0f * GetFrameTime())) + plr->y;
    }
    else
    {
        x += plr->x;
        y += plr->y;
    }

    // Check for zombies
    for (int i = 0; i < ZOMBIE_COUNT; i++)
    {
        if (plr->world->AllZombies[i] == 0)
            continue;
        Zombie* them = plr->world->AllZombies[i];
        
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

        if (CheckCollisionRecs(ourRec, theirRec))
        {
            float dx = x - them->x;
            float dy = y - them->y;
            float dist = sqrt(dx*dx + dy*dy);
            if (dist > 0.001f)
            {
                x += (dx / dist) * 1.0f;
                y += (dy / dist) * 1.0f;
            }
        }
    }

    if (!is_blocked(plr->world, x, plr->y)) plr->x = x;
    if (!is_blocked(plr->world, plr->x, y)) plr->y = y;
}

void DrawPlayer(Player *plr)
{
    DrawRectanglePro(
        (Rectangle){plr->x, plr->y, 40, 40},
        (Vector2){20, 20},
        plr->rotation * RAD2DEG,
        (Color){0xff, 0xb3, 0x19, 0xff});
}