//
// Created by siorpin on 28.05.25.
//

#ifndef AUDIOVISUALIZER_SLIDER_H
#define AUDIOVISUALIZER_SLIDER_H

#include "GuiElement.h"

class Slider final : public GuiElement {
    Color sliderColor{};
public:
    Rectangle sliderRect{};
    Vector2 valueRange{};
    Vector2 circlePosition{};
    float circleRadius = 10;

    Slider(unsigned screenWidth, unsigned screenHeight)
    : GuiElement(screenWidth, screenHeight)  {

        position = setElementPosition(screenWidth, screenHeight);
        size = setElementSize(400, 5);

        sliderRect = {position.x, position.y, size.x, size.y};
        sliderColor = {50, 50, 50, 255};
        valueRange = {position.x, size.x};

        valueRange = {position.x, position.x + size.x};
        circlePosition = {position.x + size.x / 2.0f, position.y + 2.5f};
    }

    void build() override;

    void draw() override;

    void changeSliderPosition(float x);

    float returnNewVolume();

private:
    Vector2 setElementSize(unsigned x, unsigned y) override {
        return { static_cast<float>(x), static_cast<float>(y)};
    }

    Vector2 setElementPosition(unsigned x, unsigned y) override {
        return { static_cast<float>(x) / 2, static_cast<float>(y) - 60 };
    }
};

#endif //AUDIOVISUALIZER_SLIDER_H
