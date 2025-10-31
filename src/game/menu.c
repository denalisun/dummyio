#include "menu.h"

bool RenderMenuButton(Game *game, const char* buttonText, float fontSize, Vector2 position, Color tint, Color hoverTint)
{
    Vector2 textMeasure = MeasureTextEx(game->mainFont, buttonText, fontSize, 2);
    Rectangle buttonRec = (Rectangle){
        .x = position.x,
        .y = position.y + 10,
        .width = textMeasure.x,
        .height = textMeasure.y - 20
    };
    bool bIsSelected = CheckCollisionPointRec(GetMousePosition(), buttonRec);
    DrawTextEx(game->mainFont, buttonText, position, fontSize, 2, bIsSelected ? hoverTint : tint);
    // DrawRectangleLinesEx(buttonRec, 3, WHITE);
    return bIsSelected;
}