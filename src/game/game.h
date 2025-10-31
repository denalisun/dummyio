#ifndef GAME_H
#define GAME_H

struct GameWorld;
#include "state.h"
#include "raylib.h"

typedef struct Game
{
    GameState currentState;
    Font mainFont;
    struct GameWorld* world;
} Game;

Game* ConstructGame(GameState currentState, struct GameWorld* world);

#endif
