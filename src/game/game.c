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
    gm->levelToLoad = NULL;
    return gm;
}

void SetupGameWorld(Game* game, Level* level) {
    game->currentState = STATE_INGAME;

    game->world = ConstructWorld(game, level);
    game->world->LocalUI = ConstructUI(game->world, game->mainFont);

    game->world->LocalPlayer = ConstructPlayer(200, 100, 100, 100, game->world); 

    Gun* machineGun = ConstructGun("MG-42", 0.025, 10, 120, 120, 480, 480, 3.0f, FIREMODE_AUTO);
    GiveGun(game->world->LocalPlayer, machineGun);
}
