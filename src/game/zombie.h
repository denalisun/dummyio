#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "player.h"

struct GameWorld;

typedef struct {
    float x;
    float y;
    float rotation;
    float health;
    float maxHealth;
    Rectangle hitBox;
    struct GameWorld* world;
} Zombie;

Zombie* ConstructZombie(float x, float y, float health, float maxHealth, struct GameWorld* world);
void UpdateZombie(Zombie *zm, Player *plr);
void DrawZombie(Zombie *zm);

bool is_colliding_with_another(Zombie* zm, float x, float y);

#endif