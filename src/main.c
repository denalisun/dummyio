#include "raylib.h"

int main() {
    const screen_width = 800;
    const screen_height = 600;

    InitWindow(screen_width, screen_height, "Dummy");

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(BLACK);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}