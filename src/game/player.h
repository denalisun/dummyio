#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

struct GameWorld;

typedef struct Player {
    float x;
    float y;
    float rotation;
    float health;
    float maxHealth;
    int money;
    struct GameWorld* world;
} Player;

Player* ConstructPlayer(float x, float y, float health, float maxHealth, struct GameWorld* world);
void UpdatePlayer(Player *plr);
void DrawPlayer(Player *plr);

#endif