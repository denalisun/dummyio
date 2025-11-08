#include "game.h"
#include "world.h"
#include "../utils.h"

Game* ConstructGame(GameState currentState, GameWorld* world)
{
    Game* gm = malloc(sizeof(Game));
    gm->currentState = currentState;
    gm->world = world;
    gm->bShouldClose = false;
    gm->controlType = CONTROLTYPE_MOUSE;
    gm->allMaps = get_all_maps();
    return gm;
}
