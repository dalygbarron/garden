#pragma once

/**
 * Stores constants and shit.
 */
namespace Constants {
    int const SCREEN_WIDTH = 800;
    int const SCREEN_HEIGHT = 600;
    int const TILE_SIZE = 16;
    int const TILES_WIDTH = SCREEN_WIDTH / TILE_SIZE;
    int const TILES_HEIGHT = SCREEN_HEIGHT / TILE_SIZE;
    int const N_TILES = TILES_WIDTH * TILES_HEIGHT;
};
