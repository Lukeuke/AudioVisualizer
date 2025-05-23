//
// Created by Luuqe on 22.05.2025.
//

#include "../includes/GUI/bottomBar/BottomBar.h"

sf::Vector2f BottomBar::setElementSize(const unsigned x, const unsigned y) {
    auto fX = static_cast<float>(x);
    auto fY = static_cast<float>(y) * 0.15f;

    return {fX, fY};
}

sf::Vector2f BottomBar::setElementPosition(float x, float y) {
    return {x, y - size.y};
}

void BottomBar::build() {
    bottomBar.setSize(size);
    bottomBar.setPosition(position);
    bottomBar.setFillColor(sf::Color(64, 64, 64));
}

void BottomBar::draw() {
    mainWindow->draw(bottomBar);
}
