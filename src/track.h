#ifndef TRACK_H
#define TRACK_H

#include <raylib.h>

#define TRACK_TURNS 10

typedef struct {
    Vector2 point;
    float radius;
    int left;
} Turn;

typedef struct {
    Turn turns[TRACK_TURNS];
} Track;

Track LoadTrack();

float BarrierCollision(Track* track, Vector2 pos, Vector2 dims);
int InsideTrack(Track* track, Vector2 pos);

void DrawTrack(Track* track);

#endif  // TRACK_H
