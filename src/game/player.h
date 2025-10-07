#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

typedef struct Player {
    float x;
    float y;
    float rotation;
    float health;
    float maxHealth;
    int money;
} Player;

Player* ConstructPlayer(float x, float y, float health, float maxHealth);
void UpdatePlayer(Player *plr);
void DrawPlayer(Player *plr);
Rectangle GetPlayerCollisionBox(Player *plr);

#endif