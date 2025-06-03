//
// Created by Luuqe on 29.05.2025.
//

#ifndef SIDEBAR_H
#define SIDEBAR_H

#pragma once

#include <vector>

#include "raylib.h"
#include "GuiElement.h"

class Sidebar final : public GuiElement {
    Rectangle barRect;
    Color barColor;
    std::vector<std::string> audioFiles;
    Font customFont;

public:
    Sidebar(unsigned parentWidth, unsigned parentHeight, const std::vector<std::string> &fileNames)
        : GuiElement(parentWidth, parentHeight), audioFiles(fileNames) {
        size = setElementSize(parentWidth, parentHeight);
        position = setElementPosition(0.0f, 0.0f);  // Left side by default

        barRect = { position.x, position.y, size.x, size.y };
        barColor = { 64, 64, 64, 255 };

        customFont = LoadFont("assets/fonts/OpenSans-Regular.ttf");
    }

    void build() override {
        // TODO: Add elements to sidebar
    }

    void draw() override {
        DrawRectangleRec(barRect, barColor);

        constexpr float padding = 10.0f;
        float textY = position.y + padding;

        for (const auto& file : audioFiles) {
            constexpr int fontSize = 16;
            if (textY + fontSize > position.y + size.y) break;

            DrawText(file.c_str(), position.x + padding, textY, 20, WHITE);

            // DrawTextEx(customFont, file.c_str(), { position.x + padding, textY }, 20, 2, WHITE);
            textY += fontSize + 6;
        }
    }

    ~Sidebar() override {
        UnloadFont(customFont);
    }

private:
    Vector2 setElementSize(unsigned x, unsigned y) override {
        return { static_cast<float>(x) * 0.15f, static_cast<float>(y) };  // 15% width of window
    }

    Vector2 setElementPosition(unsigned x, unsigned y) override {
        return { static_cast<float>(x), static_cast<float>(y) };  // top left
    }
};

#endif //SIDEBAR_H
