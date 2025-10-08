#include "player.h"
#include "world.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

Player* ConstructPlayer(float x, float y, float health, float maxHealth, GameWorld* world) {
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

void UpdatePlayer(Player *plr) {
    float x = ((int)IsKeyDown(KEY_D) - (int)IsKeyDown(KEY_A)) * ((float)250 * GetFrameTime());
    float y = ((int)IsKeyDown(KEY_S) - (int)IsKeyDown(KEY_W)) * ((float)250 * GetFrameTime());
    
    const Vector2 mousePos = GetMousePosition();
    plr->rotation = atan2(mousePos.y - (GetScreenHeight() / 2.0f), mousePos.x - (GetScreenWidth() / 2.0f));

    // Check for zombies
    for (int i = 0; i < ZOMBIE_COUNT; i++)
    {
        if (plr->world->AllZombies[i] == 0)
            continue;
        Zombie* them = plr->world->AllZombies[i];
        
        Rectangle ourRec = { 0 };
        ourRec.x = x;
        ourRec.y = y;
        ourRec.width = 50;
        ourRec.height = 50;

        Rectangle theirRec = { 0 };
        theirRec.x = them->x;
        theirRec.y = them->y;
        theirRec.width = 50;
        theirRec.height = 50;

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

    // Normalizing (making sure it isnt faster diagonally)
    float newX = plr->x; float newY = plr->y;
    float length = sqrtf(x*x + y*y);
    if (length > 0) {
        newX = ((x / length) * (250.0f * GetFrameTime())) + plr->x;
        newY = ((y / length) * (250.0f * GetFrameTime())) + plr->y;
    }

    if (!is_blocked(plr->world, newX, plr->y)) plr->x = newX;
    if (!is_blocked(plr->world, plr->x, newY)) plr->y = newY;
}

void DrawPlayer(Player *plr) {
    DrawRectanglePro((Rectangle){plr->x, plr->y, 50, 50}, (Vector2){25, 25}, plr->rotation * RAD2DEG, (Color){0xff, 0xb3, 0x19, 0xff});
}