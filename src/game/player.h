#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "gun.h"

#define GUN_SIZE 3

struct GameWorld;

typedef struct Player {
    float x;
    float y;
    float rotation;
    Rectangle hitBox;
    float health;
    float maxHealth;
    float timeSinceHit;
    int money;
    struct GameWorld* world;
    Camera2D* camera;
    Gun** AllGuns;
    int EquippedGun;
    bool bIsADS;
    float fireTime;
} Player;

Player* ConstructPlayer(float x, float y, float health, float maxHealth, struct GameWorld* world, Camera2D* camera);
void UpdatePlayer(Player *plr);
void DrawPlayer(Player *plr);
void SwapGun(Player *plr);
void GiveGun(Player *plr, Gun *gun);
void FireGun(Player *plr);

#endif