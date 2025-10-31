#ifndef MENU_H
#define MENU_H

#include <stdbool.h>
#include "raylib.h"
#include "game.h"

typedef enum
{
    MAIN_MENU,
    OPTIONS_MENU,
    LEVEL_SELECT_MENU,
    NO_MENU
} MenuState;

void RenderBigTitle(Game *game, const char* titleText);
bool RenderMenuButton(Game *game, const char* buttonText, float fontSize, Vector2 position, Color tint, Color hoverTint);

void RenderMainMenu(Game *game);
void RenderOptionsMenu(Game *game);
void RenderLevelSelectMenu(Game *game);

#endif
