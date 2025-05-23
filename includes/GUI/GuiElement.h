#include <SFML/Graphics.hpp>

class GuiElement {
protected:
    sf::RenderWindow* mainWindow;
    sf::Vector2u windowSize;
    sf::Vector2f size;
    sf::Vector2f position;

    virtual sf::Vector2f setElementSize(unsigned x, unsigned y) = 0;
    virtual sf::Vector2f setElementPosition(float x, float y) = 0;

public:
    GuiElement(sf::RenderWindow* mainWindow) {
        this->mainWindow = mainWindow;
        this->windowSize = mainWindow->getSize();
    }

    virtual ~GuiElement() = default;

    virtual void build() = 0;
    virtual void draw() = 0;
};