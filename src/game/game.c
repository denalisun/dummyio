#include "game.h"
#include "world.h"

Game* ConstructGame(GameState currentState, GameWorld* world)
{
    Game* gm = malloc(sizeof(Game));
    gm->currentState = currentState;
    gm->world = world;
    gm->controlType = CONTROLTYPE_MOUSE;
    return gm;
}
