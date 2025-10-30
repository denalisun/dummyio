#include "menu.h"
#include "world.h"

bool RenderMenuButton(Game *game, const char* buttonText, float fontSize, Vector2 position)
{
    Vector2 textMeasure = MeasureTextEx(game->world->LocalUI->mainFont, buttonText, fontSize, 2);
    Rectangle buttonRec = (Rectangle){
        .x = position.x,
        .y = position.y + 10,
        .width = textMeasure.x,
        .height = textMeasure.y - 20
    };
    DrawTextEx(game->world->LocalUI->mainFont, buttonText, position, fontSize, 2, WHITE);
    DrawRectangleLinesEx(buttonRec, 3, WHITE);
    return CheckCollisionPointRec(GetMousePosition(), buttonRec);
}
