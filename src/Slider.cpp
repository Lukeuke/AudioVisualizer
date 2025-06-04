//
// Created by siorpin on 28.05.25.
//

#include "raylib.h"
#include "../includes/GUI/Slider.h"

void Slider::build() {
    // TODO:
}

void Slider::draw() {
    DrawRectangleRec(sliderRect, sliderColor);
    DrawCircle(static_cast<int>(circlePosition.x), static_cast<int>(circlePosition.y), circleRadius, {0, 0, 0, 255});
}

void Slider::changeSliderPosition(float x) {
    circlePosition.x = x;
}

float Slider::returnNewVolume() {
    return (circlePosition.x - position.x) / size.x;
}