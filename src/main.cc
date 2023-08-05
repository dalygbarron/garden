#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "main/TileRenderer.hh"
#include "main/Constants.hh"
#include "main/Gui.hh"

/**
 * Entrypoint to program yeeaeeaeah.
 */
int main() {
    sf::RenderWindow window(sf::VideoMode(
        Constants::SCREEN_WIDTH,
        Constants::SCREEN_HEIGHT
    ), "Garden");
    window.setVerticalSyncEnabled(true);
    Gui::updateAspectRatio(window);
    TileRenderer renderer("data/tiles.png");
    char *hello = "hello my dear friends. I hope you beautiful day plese :) "
        "but if not, feel free to kill yourself :) ";
    int length = strlen(hello);
    for (int i = 0; i < Constants::N_TILES; i++) {
        sf::Vector2i pos(
            i % Constants::TILES_WIDTH,
            i / Constants::TILES_WIDTH
        );
        int index = i % length;
        renderer.setTile(
            pos,
            hello[index],
            sf::Color::White,
            sf::Color::Black
        );
    }
    Gui::Vbox box;
    Gui::Button *button = new Gui::Button("Hello my dearest friends", 0);
    Gui::Button *quit = new Gui::Button("Quit", 1);
    box.addChild(button);
    box.addChild(quit);
    box.setMaxBounds(sf::IntRect(5, 5, 10, 10));
    int result = Gui::runGui(window, renderer, box);
    printf("%d\n", result);
    return result;
}
