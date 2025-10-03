#include "player.h"
#include "raylib.h"
#include <stdlib.h>
#include <math.h>

Player* ConstructPlayer(float x, float y, float health, float maxHealth) {
    Player* plr = malloc(sizeof(Player));
    plr->x = x;
    plr->y = y;
    plr->rotation = 0;
    plr->health = health;
    plr->maxHealth = maxHealth;
    return plr;
}

void UpdatePlayer(Player *plr) {
    plr->x += ((int)IsKeyDown(KEY_D) - (int)IsKeyDown(KEY_A)) * ((float)500 * GetFrameTime());
    plr->y += ((int)IsKeyDown(KEY_S) - (int)IsKeyDown(KEY_W)) * ((float)500 * GetFrameTime());
    
    const Vector2 mousePos = GetMousePosition();
    plr->rotation = atan2(mousePos.y - plr->y, mousePos.x - plr->x);
}

void DrawPlayer(Player *plr) {
    DrawRectanglePro((Rectangle){plr->x, plr->y, 50, 50}, (Vector2){25, 25}, plr->rotation * RAD2DEG, (Color){0xff, 0xb3, 0x19, 0xff});
}