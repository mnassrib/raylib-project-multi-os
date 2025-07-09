#include "raylib.h"
#include "player.h"
#include "utils.h"

int main(void) {
    InitWindow(800, 600, "Raylib Project");
    SetTargetFPS(60);

    Player player = CreatePlayer();

    while (!WindowShouldClose()) {
        // Update
        UpdatePlayer(&player);

        // Draw
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawPlayer(player);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
