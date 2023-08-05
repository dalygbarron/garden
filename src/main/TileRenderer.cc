#include "TileRenderer.hh"

TileRenderer::TileRenderer(char const *textureFile):
    buffer(sf::PrimitiveType::Quads, sf::VertexBuffer::Usage::Stream)
{
    texture.loadFromFile(textureFile);
    texture.setSmooth(false);
    realTileSize = texture.getSize().x / 16;
    buffer.create(Constants::N_TILES * 8);
    for (int i = 0; i < Constants::N_TILES * 2; i++) {
        int x = ((i % Constants::N_TILES) % Constants::TILES_WIDTH) *
            Constants::TILE_SIZE;
        int y = ((i % Constants::N_TILES) / Constants::TILES_WIDTH) *
            Constants::TILE_SIZE;
        vertices[i * 4].position.x = x;
        vertices[i * 4].position.y = y;
        vertices[i * 4].texCoords = sf::Vector2f();
        vertices[i * 4 + 1].position.x = x + Constants::TILE_SIZE;
        vertices[i * 4 + 1].position.y = y;
        vertices[i * 4 + 1].texCoords = sf::Vector2f();
        vertices[i * 4 + 2].position.x = x + Constants::TILE_SIZE;
        vertices[i * 4 + 2].position.y = y + Constants::TILE_SIZE;
        vertices[i * 4 + 2].texCoords = sf::Vector2f();
        vertices[i * 4 + 3].position.x = x;
        vertices[i * 4 + 3].position.y = y + Constants::TILE_SIZE;
        vertices[i * 4 + 3].texCoords = sf::Vector2f();
    }
}

void TileRenderer::setFg(sf::Vector2i pos, uint16_t tile, sf::Color colour) {
    int index = (Constants::N_TILES + pos.y * Constants::TILES_WIDTH + pos.x) *
        4;
    int x = tile % 16;
    int y = tile / 16;
    for (int i = index; i < index + 4; i++) {
        vertices[i].color = colour;
        vertices[i].texCoords.x = (x + (i == index || i == index + 3 ? 0 : 1)) *
            realTileSize;
        vertices[i].texCoords.y = (y + (i - index) / 2) * realTileSize;
    }
}

void TileRenderer::setBg(sf::Vector2i pos, sf::Color colour) {
    int index = (pos.y * Constants::TILES_WIDTH + pos.x) * 4;
    for (int i = index; i < index + 4; i++) {
        vertices[i].color = colour;
    }
}

void TileRenderer::setTile(
    sf::Vector2i pos,
    uint16_t tile,
    sf::Color fg,
    sf::Color bg
) {
    setBg(pos, bg);
    setFg(pos, tile, fg);
}

void TileRenderer::string(
    sf::Vector2i pos,
    int maxLines,
    sf::Color fg,
    char const *text
) {
    // TODO: this.
}

void TileRenderer::marquee(
    sf::Vector2i pos,
    int length,
    sf::Color fg,
    sf::Color bg,
    char const *text
) {
    int textLength = strlen(text);
    if (textLength <= length) {
        for (int i = 0; i < textLength; i++) {
            setTile(pos + sf::Vector2i(i, 0), text[i], fg, bg);
        }
        for (int i = textLength; i < length; i++) {
            setTile(pos + sf::Vector2i(i, 0), ' ', fg, bg);
        }
    } else {
        int offset = (int)(clock.getElapsedTime().asSeconds() * MARQUEE_SPEED);
        for (int i = 0; i < length; i++) {
            int index = (offset + i) % (textLength + 1);
            char c = (index < textLength) ? text[index] : ' ';
            setTile(pos + sf::Vector2i(i, 0), c, fg, bg);
        }
    }
}

void TileRenderer::box(sf::IntRect bounds, sf::Color bg) {
    for (int x = 0; x < bounds.width; x++) {
        for (int y = 0; y < bounds.height; y++) {
            setTile(
                bounds.getPosition() + sf::Vector2i(x, y),
                ' ',
                bg,
                bg
            );
        }
    }
}

void TileRenderer::draw(
    sf::RenderTarget &target,
    sf::RenderStates states
) const {
    buffer.update(vertices);
    states.texture = &texture;
    sf::Texture::bind(&texture, sf::Texture::CoordinateType::Pixels);
    target.draw(buffer, states);
    states.texture = nullptr;
}
