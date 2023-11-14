#include "player.h"
#include <raylib.h>

#include <stdio.h>

// #define GREEN (Color){0, 255, 136, 255}

int main(void) {

    const int screenWidth = 800;
    const int screenHeight = 450;

    SetConfigFlags(FLAG_MSAA_4X_HINT);  // Enable anti-aliasing
    InitWindow(screenWidth, screenHeight, "raylib");

    SetTargetFPS(60);

    Player player;
    InitPlayer(&player);

    Texture2D car = LoadTexture("assets/orange.png");
    const float carScale = 0.2f;

    Rectangle carSrc = {0.0f, 0.0f, (float)car.width, (float)car.height};
    Rectangle carDest = {screenWidth * 0.5f, screenHeight * 0.5f, car.width * carScale, car.height * carScale};

    Vector2 carOrigin = (Vector2){car.width * carScale * 0.5f, (float)car.height * carScale * 0.5f};
    // Vector2 carOrigin = (Vector2){0.0f, 0.0f};

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

        carDest.x = player.pos.x;
        carDest.y = player.pos.y;

        // Drawing routines
        BeginDrawing();
            ClearBackground(GREEN);
            // DrawCircle(player.pos.x, player.pos.y, 10.0f, BLACK);
            // DrawLine(player.pos.x, player.pos.y, player.pos.x + player.facing.x * 20.0f, player.pos.y + player.facing.y * 20.0f, BLACK);
            
            // DrawTextureEx(car, player.pos, player.angVel, 0.1f, WHITE);
            DrawTexturePro(car, carSrc, carDest, carOrigin, player.angle * (180 / PI), WHITE);

            // DrawText("Congrats! You created your first window!", 190, 200, 20, DARKGRAY);
            
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

