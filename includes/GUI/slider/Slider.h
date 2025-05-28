//
// Created by siorpin on 28.05.25.
//

#ifndef AUDIOVISUALIZER_SLIDER_H
#define AUDIOVISUALIZER_SLIDER_H

#include "../GuiElement.h"

class Slider final: public GuiElement {
    Rectangle sliderRect;
    Color sliderColor;
    Vector2 valueRange;

public:
    Slider(unsigned parentWidth, unsigned parentHeight)
    : GuiElement(parentWidth, parentHeight)  {
        int difference;
        if(parentHeight - 20 < 0) difference = -(parentHeight - 20);
        else difference = 20;

        size = setElementSize(parentWidth, parentHeight);
        position = setElementPosition(parentWidth / 2, parentHeight - difference);

        sliderRect = {position.x, position.y, size.x, size.y};
        sliderColor = {255, 255, 255, 255};
    }

    void build() override;

    void draw() override;

private:
    Vector2 setElementSize(unsigned x, unsigned y) override {
        return { static_cast<float>(x), static_cast<float>(y)/2 };
    }

    Vector2 setElementPosition(float x, float y) override {
        return { x, y - size.y };
    }
};

#endif //AUDIOVISUALIZER_SLIDER_H
