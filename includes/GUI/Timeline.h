//
// Created by Luuqe on 03.06.2025.
//

#ifndef TIMELINE_H
#define TIMELINE_H

#include "GuiElement.h"

class Timeline final : public GuiElement {
    float _width;
    Music _music;

public:
    int timelineX;
    int timelineY;
    int timelineWidth;
    int timelineHeight;
    float musicLength;

    Timeline(int width, const Music &music) : GuiElement(width, 0) {
        _width = width = static_cast<float>(width);
        _music = music;
        musicLength = GetMusicTimeLength(music);
    }

    void build() override {
        setElementPosition(100, 60);
        setElementSize(_width - 2 * timelineX, 6);
    }

    Vector2 setElementPosition(unsigned x, unsigned y) override {
        timelineX = x;
        timelineY = y;
        return Vector2 { static_cast<float>(timelineX), static_cast<float>(timelineY) };
    }

    Vector2 setElementSize(unsigned x, unsigned y) override {
        timelineWidth = x;
        timelineHeight = y;
        return Vector2{ static_cast<float>(timelineWidth), static_cast<float>(timelineHeight)};
    }

    void draw() override {
        DrawRectangle(timelineX, timelineY, timelineWidth, timelineHeight, GRAY);

        auto musicTime = GetMusicTimePlayed(_music);
        auto progressRatio = musicLength > 0 ? musicTime / musicLength : 0.0f;

        auto markerX = timelineX + (progressRatio * timelineWidth);
        DrawRectangle(markerX - 2, timelineY - 4, 4, timelineHeight + 8, RED);

        DrawText(TextFormat("%.2fs / %.2fs", musicTime, musicLength), timelineX, timelineY - 20, 20, LIGHTGRAY);
    }

    ~Timeline() override {
    }
};

#endif //TIMELINE_H
