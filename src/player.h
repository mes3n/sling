#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>

#include "track.h"

#define PLAYER_TURN 40.0f
#define PLAYER_ACCEL 400.0f

typedef struct {
    Vector2 pos;
    float vel;
    float accel;

    float angle;
    float angVel;
    float angAccel;

    Vector2 dims;
} Player;

Player LoadPlayer(float w, float h);
void AcceleratePlayer(Player *player, float acc);
void RotatePlayer(Player *player, float angle);

void UpdatePlayer(Player *player, Track *track, float dt);

#endif  // PLAYER_H
