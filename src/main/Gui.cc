#include "Gui.hh"
#include "Util.hh"

using namespace Gui;

Element::~Element() {}

int Element::update(sf::Event &event) {
    // base implementation does nothing basically.
    return -1;
}

sf::IntRect Element::getBounds() const {
    return bounds;
}

Vbox::~Vbox() {
    for (Element *child: children) delete child;
}

void Vbox::setMaxBounds(sf::IntRect max, bool greedy) {
    sf::IntRect inner(
        max.left + 1,
        max.top + 1,
        max.width - 2,
        max.height - 2
    );
    for (int i = 0; i < children.size(); i++) {
        children[i]->setMaxBounds(inner, false);
        sf::IntRect childBounds = children[i]->getBounds();
        inner.top += childBounds.height;
        inner.height -= childBounds.height;
    }
    if (greedy) {
        bounds = max;
    } else {
        bounds = sf::IntRect(
            max.left,
            max.top,
            max.width,
            inner.top + inner.height + 1
        );
    }
}

int Vbox::update(sf::Event &event) {
    if (event.type == sf::Event::KeyPressed) {
        int motion = 0;
        if (event.key.code == sf::Keyboard::Key::Up) motion = -1;
        else if (event.key.code == sf::Keyboard::Key::Down) motion = 1;
        if (motion != 0) {
            selectedItem = (selectedItem + motion) % children.size();
            return -1;
        }
    }
    return children[selectedItem]->update(event);
}

void Vbox::render(TileRenderer &renderer, bool selected) const {
    renderer.box(bounds, sf::Color::Green);
    for (int i = 0; i < children.size(); i++) {
        children[i]->render(renderer, selected && i == selectedItem);
    }
}

void Vbox::addChild(Element *child) {
    children.push_back(child);
}

Button::Button(char const *text, int returnValue): returnValue(returnValue) {
    this->text = Util::copyString(text);
}

Button::~Button() {
    delete[] text;
}

void Button::setMaxBounds(sf::IntRect max, bool greedy) {
    bounds = sf::IntRect(
        max.left,
        max.top,
        max.width,
        1
    );
}

int Button::update(sf::Event &event) {
    if (
        event.type == sf::Event::KeyPressed &&
        event.key.code == sf::Keyboard::Key::Space
    ) {
        return returnValue;
    }
    return -1;
}

void Button::render(TileRenderer &renderer, bool selected) const {
    renderer.marquee(
        bounds.getPosition(),
        bounds.width,
        sf::Color::White,
        selected ? sf::Color::Blue : sf::Color::Black,
        text
    );
}

Text::Text(char const *string) {
    unwrapped = Util::copyString(string);
}

Text::~Text() {
    delete[] unwrapped;
    // TODO: delete the wrapped text probably.
}

void Text::setMaxBounds(sf::IntRect max, bool greedy) {
    // TODO: wrap text and base size on that.
}

void Text::render(TileRenderer &renderer, bool selected) const {
    if (wrapped != nullptr) {
        renderer.string(
            bounds.getPosition(),
            bounds.height,
            sf::Color::White,
            wrapped
        );
    }
}

void Gui::updateAspectRatio(sf::RenderWindow &window) {
    sf::Vector2u size = window.getSize();
    sf::View view = window.getView();
    float naturalRatio = (float)Constants::SCREEN_WIDTH /
        (float)Constants::SCREEN_HEIGHT;
    float xRatio = (float)size.x / (float)size.y;
    float yRatio = (float)size.y / (float)size.x;
    float newViewWidth = Constants::SCREEN_WIDTH;
    if (xRatio >= naturalRatio) {
        view.setSize({
            Constants::SCREEN_HEIGHT * xRatio,
            Constants::SCREEN_HEIGHT
        });
    } else {
        view.setSize({
            Constants::SCREEN_WIDTH,
            Constants::SCREEN_WIDTH * yRatio
        });
    }
    window.setView(view);
}

int Gui::runGui(
    sf::RenderWindow &window,
    TileRenderer &renderer,
    Element &element
) {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::Resized) {
                updateAspectRatio(window);
            } else {
                int result = element.update(event);
                if (result != -1) return result;
            }
        }
        element.render(renderer, true);
        window.clear(sf::Color::Black);
        window.draw(renderer);
        window.display();
    }
    return 0;
}