#pragma once

#include "TileRenderer.hh"

/**
 * Contains the actual game state and facilitates saving and loading. In terms
 * of program flow this class basically takes control and handles the main loop.
 */
class Game {
    private:
        TileRenderer &renderer;

    public:
        /**
         * Creates the game object but without loading in any save state or
         * anything.
         * @param renderer is the tile renderer used to render shit.
         */
        Game(TileRenderer &renderer);

        /**
         * Essentially this is the main loop of the game. Once this is called,
         * it will not return until the game is done.
         */
        void main();
};