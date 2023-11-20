#include "player.h"

#include <raymath.h>

#include "raylib.h"
#include "track.h"

#define Vector2Identity \
    (Vector2) { 0.0f, -1.0f }

// TODO: Load player by ref instead of pointer
Player LoadPlayer(float w, float h) {
    Player player;

    player.pos = (Vector2){400.0f, 500.0f};
    player.vel = 0.0f;
    player.accel = 0.0f;

    player.angle = 0.0f;
    player.angVel = 0.0f;
    player.angAccel = 0.0f;

    player.dims.x = w;
    player.dims.y = h;

    return player;
}

void AcceleratePlayer(Player *player, const float acc) { player->accel += acc; }

void RotatePlayer(Player *player, const float angle) {
    player->angAccel += angle;
}

#define ABSF(x) (x < 0.0f ? -x : x)

void UpdatePlayer(Player *player, Track *track, const float dt) {
    // Update positiom
    player->vel += player->accel * dt;
    Vector2 v = Vector2Rotate(Vector2Scale(Vector2Identity, player->vel * dt),
                              player->angle);
    float y = BarrierCollision(track, player->pos, player->dims);
    if (y >= 0.0f) {
        if ((player->pos.y > y && v.y < 0.0f) ||
            (player->pos.y < y && v.y > 0.0f)) {
            v.y = 0.0f;
        }
    }
    player->pos = Vector2Add(player->pos, v);

    // Update rotaion
    player->angVel +=
        player->angAccel * dt *
        Clamp(ABSF(player->vel) * 0.01f, 0.0f, 1.0f);  // Turn based on velocity
    player->angle +=
        player->angVel * dt *
        (player->vel > 0.0f ? 1.0f : -1.0f);  // Turn like a real car

    // Apply friction // Add more friciton when turning
    player->vel *= 0.98f;
    // player->vel *= (1.0f - Clamp(ABSF(player->angVel) * 0.005, 0.0f, 0.0f));
    player->angVel *= 0.8f;

    if (!InsideTrack(track, player->pos)) {
        player->vel *= 0.94f;
    }
}
