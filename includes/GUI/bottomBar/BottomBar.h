#pragma once
#include "../GuiElement.h"

class BottomBar final : public GuiElement {
    Rectangle barRect;
    Color barColor;

public:
    BottomBar(unsigned screenWidth, unsigned screenHeight)
        : GuiElement(screenWidth, screenHeight) {
        size = setElementSize(screenWidth, screenHeight);
        position = setElementPosition(0.0f, windowSize.y);

        barRect = { position.x, position.y, size.x, size.y };
        barColor = { 64, 64, 64, 255 };
    }

    void build() override;

    void draw() override;
private:
    Vector2 setElementSize(unsigned x, unsigned y) override {
        return { static_cast<float>(x), static_cast<float>(y) * 0.15f };
    }

    Vector2 setElementPosition(float x, float y) override {
        return { x, y - size.y };
    }
};
