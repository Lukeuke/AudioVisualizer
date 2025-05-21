#include <SFML/Graphics.hpp>

#include "../GuiElement.h"
#include "components/Button.h"

class BottomBar : public GuiElement {
    private:
        sf::RectangleShape bottomBar;

    sf::Vector2f setElementSize(unsigned x, unsigned y) override {
        float fX = static_cast<float>(x);
        float fY = static_cast<float>(y) *0.15f;

        return sf::Vector2f(fX, fY);
    }

    sf::Vector2f setElementPosition(float x, float y) override {
        return sf::Vector2f(x, y - size.y);
    }

    public:
        BottomBar(sf::RenderWindow* mainWindow)
            : GuiElement(mainWindow) {
            this->windowSize = mainWindow->getSize();
            this->size = setElementSize(windowSize.x, windowSize.y);
            this->position = setElementPosition(0.f, static_cast<float>(windowSize.y));
        }
    
        void build() override {
            bottomBar.setSize(size);
            bottomBar.setPosition(position);
            bottomBar.setFillColor(sf::Color(64, 64, 64));
        }

        void draw() override {
            mainWindow->draw(bottomBar);
        }
    };