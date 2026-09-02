#ifndef CONSTANTS_H
#define CONSTANTS_H

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

// Reference tile size in pixels at the default (unscaled) resolution above.
// Entity movement lives in tile units; this is only used to derive the
// playable grid size in tiles and as the baseline for pixel scaling.
#define TILE_SIZE 32
#define TILEMAP_TILES_X (SCREEN_WIDTH / TILE_SIZE)
#define TILEMAP_TILES_Y (SCREEN_HEIGHT / TILE_SIZE)

#endif // CONSTANTS_H
