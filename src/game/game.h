#ifndef GAME_H
#define GAME_H

struct GameWorld;
#include "state.h"
#include "raylib.h"

typedef enum ControlType
{
    CONTROLTYPE_MOUSE,
    CONTROLTYPE_KEYBOARD,
    CONTROLTYPE_CONTROLLER
} ControlType;

typedef struct Game
{
    GameState currentState;
    Font mainFont;
    struct GameWorld* world;
    
    // Settings
    ControlType controlType;

    // Asset data
    char** allMaps;
} Game;

Game* ConstructGame(GameState currentState, struct GameWorld* world);

#endif
