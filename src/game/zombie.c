#include "zombie.h"
#include "raylib.h"
#include <stdlib.h>
#include <math.h>

Zombie* ConstructZombie(float x, float y, float health, float maxHealth) {
    Zombie* zm = malloc(sizeof(Zombie));
    zm->x = x;
    zm->y = y;
    zm->rotation = 0;
    zm->health = health;
    zm->maxHealth = maxHealth;
    return zm;
}

void UpdateZombie(Zombie *zm, Player *plr) {
    zm->rotation = atan2(zm->y - plr->y, zm->x - plr->x);
    zm->x -= cos(zm->rotation) * ((float)100 * GetFrameTime());
    zm->y -= sin(zm->rotation) * ((float)100 * GetFrameTime());

    //TODO: Detect Collision using Box2D
}

void DrawZombie(Zombie *zm) {
    DrawRectanglePro((Rectangle){zm->x, zm->y, 50, 50}, (Vector2){25, 25}, zm->rotation * RAD2DEG, GREEN);
}