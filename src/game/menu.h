#ifndef MENU_H
#define MENU_H

#include <stdbool.h>
#include "raylib.h"
#include "game.h"

typedef enum
{
    MAIN_MENU,
    OPTIONS_MENU,
} MenuState;

bool RenderMenuButton(Game *game, const char* buttonText, float fontSize, Vector2 position, Color tint, Color hoverTint);

#endif
