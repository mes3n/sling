#include <raylib.h>

#include "player.h"
#include "sprite.h"

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 1000;

    SetTraceLogLevel(LOG_NONE);  
    SetConfigFlags(FLAG_MSAA_4X_HINT);  // Enable anti-aliasing

    InitWindow(screenWidth, screenHeight, "raylib");

    SetTargetFPS(60);

    Player player;
    InitPlayer(&player);

    SpriteSheet carSheet = LoadSpriteSheet("assets/orange.png", 2, 0.2f);

    int ticker = 0;
    while (!WindowShouldClose()) {
        // Event Handling
        if (IsKeyPressed(KEY_W)) {
            AcceleratePlayer(&player, PLAYER_ACCEL);
        } else if (IsKeyReleased(KEY_W)) {
            AcceleratePlayer(&player, -PLAYER_ACCEL);
        }
        if (IsKeyPressed(KEY_S)) {
            AcceleratePlayer(&player, -PLAYER_ACCEL * 0.5f);
        } else if (IsKeyReleased(KEY_S)) {
            AcceleratePlayer(&player, PLAYER_ACCEL * 0.5f);
        }

        if (IsKeyPressed(KEY_A)) {
            RotatePlayer(&player, -PLAYER_TURN);
        } else if (IsKeyReleased(KEY_A)) {
            RotatePlayer(&player, PLAYER_TURN);
        }
        if (IsKeyPressed(KEY_D)) {
            RotatePlayer(&player, PLAYER_TURN);
        } else if (IsKeyReleased(KEY_D)) {
            RotatePlayer(&player, -PLAYER_TURN);
        }

        float dt = GetFrameTime();

        // Update entities
        UpdatePlayer(&player, dt);

        // Drawing routines
        BeginDrawing();
        ClearBackground(GREEN);

#define ABS(x) (x < 0.0f ? -x : x)

        DrawSprite(
            &carSheet,
            (int)(ticker * 0.02f * (ABS(player.accel) * 0.005f + 1.0f)) % 2,
            player.pos, player.angle);

        EndDrawing();

        ticker++;
    }

    UnloadSpriteSheet(carSheet);
    CloseWindow();
    return 0;
}
