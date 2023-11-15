#ifndef SPRITE_H
#define SPRITE_H

#include <raylib.h>

typedef struct {
    Rectangle source;
    Rectangle dest;

    Vector2 origin;
} Sprite;

typedef struct {
    Rectangle* sources;
    int sourceCount;

    Texture2D sheet;

    Rectangle dest;
    Vector2 origin;

    float scale;
} SpriteSheet;

/**
 * LoadSpriteSheet assumes all loaded sprites are of equal dimension
 * @param spriteCount determines how many sprites the horisontally tiled
 * sheet will be split into
 */
SpriteSheet LoadSpriteSheet(const char* filename, int spriteCount, float scale);

void DrawSprite(SpriteSheet* sheet, int i, Vector2 position, float rotation);

void UnloadSpriteSheet(SpriteSheet sheet);

#endif  // SPRITE_H
