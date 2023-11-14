#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>

#define PLAYER_TURN 40.0f
#define PLAYER_ACCEL 400.0f

typedef struct {
    Vector2 pos;
    float vel;
    float accel;

    float angle;
    float angVel;
    float angAccel;
} Player;

void InitPlayer(Player *player);
void AcceleratePlayer(Player *player, float acc);
void RotatePlayer(Player *player, float angle);

void UpdatePlayer(Player *player, float dt);

#endif  // PLAYER_H
