#pragma once

#include "TileRenderer.hh"

/**
 * All gui elements are in this namespace.
 */
namespace Gui {
    /**
     * Base class of gui elements.
     */
    class Element {
        protected:
            sf::IntRect bounds;

        public:
            /**
             * Virtual destructor so they can do whatever they wanna do.
             */
            virtual ~Element();

            /**
             * Tells the element the maximum bounds it can have and updates it.
             * @param max is the new maximum bounds.
             * @param greedy is whether to just take the maximum bounds as the
             *        new bounds or to calculate the needed space. Some elements
             *        might not actually be capable of utilising all the space,
             *        so they will still set themselves as being smaller.
             */
            virtual void setMaxBounds(sf::IntRect max, bool greedy=true) = 0;

            /**
             * Updates the element with an input event. You can send any event
             * because it will just filter the irrelevant ones out.
             * @param event is the input event we are responding to.
             * @return a number which if -1 is interpreted as meaning nothing.
             *         Any other return value means something meaningful and
             *         that the gui system should stop.
             */
            virtual int update(sf::Event &event);

            /**
             * Renders the element upon it's point on the screen where it goes.
             * @param renderer is used to render stuff.
             * @param selected is whether this element is currently selected by
             *                 it's parent to be highlighted.
            */
            virtual void render(
                TileRenderer &renderer,
                bool selected
            ) const = 0;

            /**
             * Gives you the element's current bounds.
             * @return the bounds rect.
             */
            sf::IntRect getBounds() const;
    };

    /**
     * A box that contains some childrens.
     */
    class Vbox: public Element {
        private:
            std::vector<Element *> children;
            int selectedItem = 0;

        public:
            virtual ~Vbox() override;

            virtual void setMaxBounds(
                sf::IntRect max,
                bool greedy=true
            ) override;

            virtual int update(sf::Event &event) override;

            virtual void render(
                TileRenderer &renderer,
                bool selected
            ) const override;

            /**
             * Adds a child element to the vbox.
             * @param child is the child.
             */
            void addChild(Element *child);
    };

    /**
     * A button that the user can activate that shows text.
     */
    class Button: public Element {
        private:
            char const *text;
            int const returnValue;

        public:
            /**
             * Creates the button by giving it some text to have on it, and a
             * value to return if it is clicked.
             * @param text is the text it should have on it. The actual
             *        characters will be copied to a new array so that we don't
             *        need to worry where this text came from.
             * @param returnValue is the value to return if this button is
             *        pressed.
             */
            Button(char const *text, int returnValue);

            virtual ~Button() override;

            virtual void setMaxBounds(
                sf::IntRect max,
                bool greedy=true
            ) override;

            virtual int update(sf::Event &event) override;

            virtual void render(
                TileRenderer &renderer,
                bool selected
            ) const override;
    };

    /**
     * An element that shows wrapped text.
     */
    class Text: public Element {
        private:
            char *unwrapped;
            char *wrapped = nullptr;

        public:
            /**
             * Creates the text object by giving it the unwrapped text it needs
             * to show.
             * @param string is the text to show which it will copy.
             */
            Text(char const *string);

            virtual ~Text() override;

            virtual void setMaxBounds(
                sf::IntRect max,
                bool greedy=true
            ) override;

            virtual void render(
                TileRenderer &renderer,
                bool selected
            ) const override;
    };

    /**
     * Updates the aspect ratio of the game's view to fit the window's current
     * dimensions.
     * @param window is the game window.
     */
    void updateAspectRatio(sf::RenderWindow &window);

    /**
     * Makes a gui element take over the main loop and render and take input
     * until it is done.
     * @param window is the game window which we get input from.
     * @param renderer is used to render the gui element.
     * @param element is the gui element to put on the screen.
     */
    int runGui(
        sf::RenderWindow &window,
        TileRenderer &renderer,
        Element &element
    );
};