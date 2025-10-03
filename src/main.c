#include "raylib.h"
#include "game/player.h"

int main(void)
{
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Dummy");

    Player* plr = ConstructPlayer(100, 100, 100, 100);

    while (!WindowShouldClose()) {
        UpdatePlayer(plr);

        BeginDrawing();
        ClearBackground(BLACK);
        DrawFPS(10, screenHeight - 30);

        DrawPlayer(plr);

        EndDrawing();
    }

    CloseWindow();
    
    return 0;
}