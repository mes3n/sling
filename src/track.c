#include "track.h"

#include <raymath.h>
#include <rlgl.h>

#include "raylib.h"

#define TRACK_WIDTH 150.0f

Track LoadTrack() {
    Track track;

    for (int i = 0; i < TRACK_TURNS; i++) {
        Turn turn;

        int r;
        if (i & 1) {
            r = GetRandomValue(100, 300);
        } else {
            r = GetRandomValue(500, 650);
        }

        turn.radius = TRACK_WIDTH;
        turn.point = (Vector2){(float)r, 200.0f * i};
        turn.left = i & 1;

        track.turns[i] = turn;
    }

    return track;
}

#define ABSF(x) (x < 0.0f ? -x : x)
#include <stdio.h>

float BarrierCollision(Track* track, Vector2 p, Vector2 d) {
    for (int i = 0; i < TRACK_TURNS; i++) {
        Turn turn = track->turns[i];

        Vector2 poss[4] = {
            (Vector2){p.x + d.x * 0.5f, p.y + d.y * 0.5f},
            (Vector2){p.x - d.x * 0.5f, p.y + d.y * 0.5f},
            (Vector2){p.x + d.x * 0.5f, p.y - d.y * 0.5f},
            (Vector2){p.x - d.x * 0.5f, p.y - d.y * 0.5f},
        };

        for (int j = 0; j < 4; j++) {
            if ((turn.left && poss[j].x < turn.point.x) ||
                (!turn.left && poss[j].x > turn.point.x)) {
                continue;
            }

            float d = turn.point.y - poss[j].y;
            if (ABSF(d) < 3.0f) {
                return turn.point.y;
            }
        }
    }
    return -1.0f;
}

int InsideTrack(Track* track, Vector2 pos) {
    int i = 0;
    for (; i < TRACK_TURNS; i++) {
        Turn turn = track->turns[i];

        if ((turn.left && pos.x <= turn.point.x) ||
            (!turn.left && pos.x >= turn.point.x)) {
            if (CheckCollisionPointCircle(pos, turn.point,
                                          turn.radius - 4.0f)) {
                return 1;
            }
        }
    }
    for (i = 1; i < TRACK_TURNS; i++) {
        Vector2 v1 = track->turns[i - 1].point;
        v1.y += TRACK_WIDTH - 4.0f;  // * (i & 1 ? 1 : -1);
        Vector2 v2 = track->turns[i].point;
        v2.y -= TRACK_WIDTH - 4.0f;  // * (i & 1 ? -1 : 1);

        Vector2 points[4] = {track->turns[i - 1].point, v1,
                             track->turns[i].point, v2};

        if (CheckCollisionPointPoly(pos, points, 4)) {
            return 1;
        }
    }
    return 0;
}

void DrawTrack(Track* track) {
    int i = 1;
    for (; i < TRACK_TURNS; i++) {
        Vector2 v1 = track->turns[i - 1].point;
        v1.y += TRACK_WIDTH * 0.5f;  // * (i & 1 ? 1 : -1);
        Vector2 v2 = track->turns[i].point;
        v2.y -= TRACK_WIDTH * 0.5f;  // * (i & 1 ? -1 : 1);

        DrawLineBezier(v1, v2, TRACK_WIDTH, DARKGRAY);
        DrawLineBezier(v1, v2, 4.0f, RAYWHITE);
    }
    for (i = 0; i < TRACK_TURNS; i++) {
        Turn turn = track->turns[i];

        float angleStart = turn.left ? 270.0f : -90.0f;
        float angleEnd = 90.0f;

        DrawCircleSector(turn.point, turn.radius, angleStart, angleEnd, 24,
                         DARKGRAY);
        DrawCircleSector(turn.point, turn.radius * 0.5f + 2.0f, angleStart,
                         angleEnd, 24, RAYWHITE);
        DrawCircleSector(turn.point, turn.radius * 0.5f - 2.0f, angleStart,
                         angleEnd, 24, DARKGRAY);

        DrawLineEx(turn.point,
                   (Vector2){turn.left ? 800.0f : 0.0f, turn.point.y}, 6.0f,
                   PURPLE);

        DrawCircleV(turn.point, 12.0f, PURPLE);
        DrawCircleV(turn.point, 4.0f, DARKPURPLE);
    }
}
