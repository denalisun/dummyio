#ifndef PLAYER_H
#define PLAYER_H

typedef struct PLAYER {
    float x;
    float y;
    float rotation;
    float health;
    float maxHealth;
} Player;

Player* ConstructPlayer(float x, float y, float health, float maxHealth);
void UpdatePlayer(Player *plr);
void DrawPlayer(Player *plr);

#endif