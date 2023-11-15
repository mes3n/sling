#include "sprite.h"

// TODO: Implement 2d tiling for sheet
SpriteSheet LoadSpriteSheet(const char *filename, int spriteCount,
                            float scale) {
    SpriteSheet spriteSheet;

    spriteSheet.sheet = LoadTexture(filename);
    spriteSheet.sources =
        (Rectangle *)MemAlloc(spriteCount * sizeof(Rectangle));

    const int width = spriteSheet.sheet.width;
    const int height = spriteSheet.sheet.height;

    const float spriteWidth = (float)width / (float)spriteCount;

    spriteSheet.dest =
        (Rectangle){0.0f, 0.0f, spriteWidth * scale, (float)height * scale};
    spriteSheet.origin =
        (Vector2){spriteWidth * 0.5f * scale, (float)height * 0.5f * scale};

    for (int i = 0; i < spriteCount; i++) {
        spriteSheet.sources[i] = (Rectangle){spriteWidth * (float)i, 0.0f,
                                             (float)spriteWidth, (float)height};
    }

    return spriteSheet;
}

void DrawSprite(SpriteSheet *sheet, int i, Vector2 position, float rotation) {
    sheet->dest.x = position.x;
    sheet->dest.y = position.y;

    DrawTexturePro(sheet->sheet, sheet->sources[i], sheet->dest, sheet->origin,
                   rotation * RAD2DEG, WHITE);
}

void UnloadSpriteSheet(SpriteSheet sheet) {
    UnloadTexture(sheet.sheet);
    MemFree(sheet.sources);
}
