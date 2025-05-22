#include <SFML/Graphics.hpp>

#include "../GuiElement.h"

class BottomBar : public GuiElement {
sf::RectangleShape bottomBar;

public:
    BottomBar(sf::RenderWindow* mainWindow)
        : GuiElement(mainWindow) {
        this->windowSize = mainWindow->getSize();
        this->size = BottomBar::setElementSize(windowSize.x, windowSize.y);
        this->position = BottomBar::setElementPosition(0.f, static_cast<float>(windowSize.y));
    }
    void build() override;
    void draw() override;

private:
    sf::Vector2f setElementSize(unsigned x, unsigned y) override;
    sf::Vector2f setElementPosition(float x, float y) override;
};