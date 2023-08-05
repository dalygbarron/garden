#pragma once

#include <SFML/Graphics.hpp>
#include <stdint.h>
#include "Constants.hh"

/**
 * This is the renderer that renders everything in the game. Basically it makes
 * a buffer of tile looking thingies, and then it renders them real nicely, and
 * it provides a few different ways of modifying this buffer.
 */
class TileRenderer: public sf::Drawable {
    private:
        sf::Clock clock;
        sf::Vertex vertices[Constants::N_TILES * 8];
        mutable sf::VertexBuffer buffer;
        sf::Texture texture;
        int realTileSize;
        float const MARQUEE_SPEED = 4.4;

    public:
        /**
         * Creates the tile renderer.
         * @param textureFile is the path to the tiles texture.
         */
        TileRenderer(char const *textureFile);

        /**
         * Sets the foreground of a given tile.
         * @param pos is the screen position of the tile to change.
         * @param tile is the tile image to display on it.
         * @param colour is the colour to draw the image with.
         */
        void setFg(sf::Vector2i pos, uint16_t tile, sf::Color colour);

        /**
         * Sets the background of a given tile.
         * @param pos is the screen position of the tile to change.
         * @param colour is the colour to draw the background with.
         */
        void setBg(sf::Vector2i pos, sf::Color colour);

        /**
         * Sets the foreground and background of a tile.
         * @param pos is the screen position of the tile to change.
         * @param tile is the image on the tile.
         * @param fg is the colour of the image.
         * @param bg is the colour of the background.
         */
        void setTile(
            sf::Vector2i pos,
            uint16_t tile,
            sf::Color fg,
            sf::Color bg
        );

        /**
         * Render a string to the screen at the given location, doesn't change
         * background colours.
         * @param pos is the position of the first character of text.
         * @param maxLines is the maximum number of lines of text before it is
         *                 truncated.
         * @param fg is the colour of the text.
         * @param text is the text to render.
         */
        void string(
            sf::Vector2i pos,
            int maxLines,
            sf::Color fg,
            char const *text
        );

        /**
         * Renders text, and marquees it if it is too long, by using an internal
         * clock to figure out which characters to render at any given time.
         * @param pos is the position of the first character.
         * @param length is the maximum characters to show at once.
         * @param fg is the foreground colour of the text.
         * @param bg is the background colour of the text.
         * @param text is the text to render.
         */
        void marquee(
            sf::Vector2i pos,
            int length,
            sf::Color fg,
            sf::Color bg,
            char const *text
        );

        /**
         * Draws an empty box of plain colour upon the screen.
         * @param bounds is the dimensions and position  of the box.
         * @param bg is the colour to fill.
         */
        void box(sf::IntRect bounds, sf::Color bg);

        virtual void draw(
            sf::RenderTarget &target,
            sf::RenderStates states
        ) const override;
};
