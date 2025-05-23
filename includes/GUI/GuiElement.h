#pragma once
#include "raylib.h"

class GuiElement {
protected:
    Vector2 windowSize{};
    Vector2 size{};
    Vector2 position{};

    virtual Vector2 setElementSize(unsigned x, unsigned y) = 0;
    virtual Vector2 setElementPosition(float x, float y) = 0;

public:
    GuiElement(const unsigned screenWidth, const unsigned screenHeight) {
        windowSize = { static_cast<float>(screenWidth), static_cast<float>(screenHeight) };
    }

    virtual ~GuiElement() = default;

    virtual void build() = 0;
    virtual void draw() = 0;
};
