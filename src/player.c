#include "player.h"

#include <raymath.h>

#define Vector2Identity (Vector2){0.0f, -1.0f}


void InitPlayer(Player *player) {
    player->pos = (Vector2){400.0f, 225.0f};
    player->vel = 0.0f;
    player->accel = 0.0f;

    player->angle = 0.0f;
    player->angVel = 0.0f;
    player->angAccel = 0.0f;
}

void AcceleratePlayer(Player *player, const float acc) {
    player->accel += acc;
}

void RotatePlayer(Player *player, const float angle) {
    player->angAccel += angle;
}

#define ABSF(x) (x < 0.0f ? -x : x)

void UpdatePlayer(Player *player, const float dt) {
    // Update positiom
    player->vel += player->accel * dt;
    player->pos = Vector2Add(player->pos, 
            Vector2Rotate(
                Vector2Scale(Vector2Identity, player->vel * dt), 
                player->angle));

    // Update rotaion
    player->angVel += player->angAccel * dt * 
        Clamp(ABSF(player->vel) * 0.01f, 0.0f, 1.0f);  // Turn based on velocity
    player->angle += player->angVel * dt * 
        (player->vel > 0.0f ? 1.0f : -1.0f);  // Turn like a real car

    // Apply friction // Add more friciton when turning
    player->vel *= 0.98f * 
        (1.0f - Clamp(ABSF(player->angVel) * 0.005, 0.0f, 0.0f));  
    player->angVel *= 0.8f;
}
