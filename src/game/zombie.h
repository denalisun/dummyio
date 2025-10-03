#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "box2d.h"
#include "player.h"

typedef struct {
    float x;
    float y;
    float rotation;
    float health;
    float maxHealth;
} Zombie;

Zombie* ConstructZombie(float x, float y, float health, float maxHealth);
void UpdateZombie(Zombie *zm, Player *plr);
void DrawZombie(Zombie *zm);

#endif