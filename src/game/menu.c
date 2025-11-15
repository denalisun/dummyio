#include "menu.h"
#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include "../core/json_handler.h"
#include "world.h"

void RenderBigTitle(Game *game, const char* titleText)
{
    int screenWidth = GetScreenWidth();

    Vector2 titleTextMeasurement = MeasureTextEx(game->mainFont, titleText, 184, 2);
    DrawTextEx(game->mainFont, titleText, (Vector2){ screenWidth - titleTextMeasurement.x, 0 }, 184, 2, WHITE);
    DrawLineEx((Vector2){ screenWidth, titleTextMeasurement.y - 20 }, (Vector2){ (int)(screenWidth / 2), titleTextMeasurement.y - 20 }, 10, WHITE);
}

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

const Color unselectedColor = {46, 65, 102, 255};
const Color selectedColor = {75, 120, 166, 255};

void RenderMainMenu(Game *game)
{
    BeginDrawing();
    ClearBackground((Color){11, 9, 20, 255});
      
    int screenHeight = GetScreenHeight();
        
    RenderBigTitle(game, "DUMMY");

    char copyrightText[] = "created by denalisun (c) 2025";
    Vector2 copyrightMeasurement = MeasureTextEx(game->mainFont, copyrightText, 24, 2);
    DrawTextEx(game->mainFont, copyrightText, (Vector2){ 5, screenHeight - copyrightMeasurement.y }, 24, 2, WHITE);
        
    // Selections
    bool bIsPlayButtonSelected = RenderMenuButton(game, "PLAY", 72, (Vector2){ 20, 250 }, unselectedColor, selectedColor);
    bool bIsOptionsButtonSelected = RenderMenuButton(game, "OPTIONS", 72, (Vector2){ 20, 310 }, unselectedColor, selectedColor);
    bool bIsQuitButtonPressed = RenderMenuButton(game, "QUIT", 72, (Vector2){ 20, 370 }, unselectedColor, selectedColor);

    if (bIsPlayButtonSelected && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        game->currentState = STATE_LEVELSELECTIONMENU;
    }

    if (bIsOptionsButtonSelected && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        game->currentState = STATE_OPTIONSMENU;
    }

    if (bIsQuitButtonPressed && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        game->bShouldClose = true;
    }

    EndDrawing();
}

void RenderOptionsMenu(Game *game)
{
    BeginDrawing();
    ClearBackground((Color){ 11, 9, 20, 255 });

    int screenHeight = GetScreenHeight();

    RenderBigTitle(game, "OPTIONS");

    // This is broken for some reason but Ill fix it later
    char controlTypeText[32];
    switch (game->controlType)
    {
        case CONTROLTYPE_CONTROLLER:
            strcpy(controlTypeText, "Control Type: Controller");
            break;

        case CONTROLTYPE_KEYBOARD:
            strcpy(controlTypeText, "Control Type: Keyboard");
            break;

        case CONTROLTYPE_MOUSE:
            strcpy(controlTypeText, "Control Type: KBM");
            break;
    }
    bool bControlTypeSelected = RenderMenuButton(game, controlTypeText, 72, (Vector2){ 20, 250 }, unselectedColor, selectedColor);

    bool bQuitButtonSelected = RenderMenuButton(game, "BACK", 72, (Vector2){ 20, (screenHeight - 72) }, unselectedColor, selectedColor);

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (bControlTypeSelected)
        {
            if (game->controlType == CONTROLTYPE_CONTROLLER) game->controlType = CONTROLTYPE_KEYBOARD;
            if (game->controlType == CONTROLTYPE_KEYBOARD) game->controlType = CONTROLTYPE_MOUSE;
            if (game->controlType == CONTROLTYPE_MOUSE) game->controlType = CONTROLTYPE_CONTROLLER;
        }

        if (bQuitButtonSelected)
        {
            game->currentState = STATE_MAINMENU;
        }
    }

    EndDrawing();
}

void RenderLevelSelectMenu(Game *game)
{
    BeginDrawing();
    ClearBackground((Color){ 11, 9, 20, 255 });

    int screenHeight = GetScreenHeight();
    
    RenderBigTitle(game, "SELECT MAP");

    bool bQuitButtonSelected = RenderMenuButton(game, "BACK", 72, (Vector2){ 20, (screenHeight - 72) }, unselectedColor, selectedColor);

    for (int i = 0; i < ((int)sizeof(game->allMaps) / (int)sizeof(game->allMaps[0])); i++)
    {
        char* map_name = game->allMaps[i];
        bool bIsMapButtonPressed = RenderMenuButton(game, map_name, 36, (Vector2){ 20, 250 + (10 * i) }, unselectedColor, selectedColor);
        if (bIsMapButtonPressed && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            //printf("Awesome! %s\n", map_name);
            //game->currentState = STATE_INGAME;
            char mapPath[22 + strlen(map_name)];
            sprintf(mapPath, "assets/maps/%s/map.json", map_name);

            Level* lvl = ProcessMapJSON(mapPath);
            if (lvl == 0) {
                printf("Augh\n");
            } else {
                GameWorld* world = ConstructWorld(game, lvl);
                world->LocalUI = ConstructUI(world, game->mainFont);
            }
        }
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (bQuitButtonSelected)
        {
            game->currentState = STATE_MAINMENU;
        }
    }

    EndDrawing();
}
