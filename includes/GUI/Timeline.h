//
// Created by Luuqe on 03.06.2025.
//

#ifndef TIMELINE_H
#define TIMELINE_H

#include "GuiElement.h"

/**
 * @class Timeline
 * @brief Element GUI przedstawiający pasek postępu odtwarzania muzyki.
 *
 * Klasa Timeline odpowiada za wizualne przedstawienie aktualnego czasu
 * odtwarzania utworu muzycznego. Wyświetla prostokątny pasek z markerem
 * wskazującym aktualną pozycję oraz czasem odtwarzania.
 */
class Timeline final : public GuiElement {
    float _width;     ///< Całkowita szerokość komponentu Timeline
    Music _music;     ///< Obiekt muzyki, którego odtwarzanie jest śledzone

public:
    int timelineX;        ///< Pozycja X paska na ekranie
    int timelineY;        ///< Pozycja Y paska na ekranie
    int timelineWidth;    ///< Szerokość paska postępu
    int timelineHeight;   ///< Wysokość paska postępu
    float musicLength;    ///< Długość utworu muzycznego (w sekundach)

    /**
     * @brief Konstruktor klasy Timeline.
     * @param width Szerokość całkowita elementu GUI.
     * @param music Obiekt muzyki do śledzenia.
     */
    Timeline(int width, const Music &music) : GuiElement(width, 0) {
        _width = static_cast<float>(width);
        _music = music;
        musicLength = GetMusicTimeLength(music);
    }

    /**
     * @brief Buduje element GUI, ustawiając jego pozycję i rozmiar.
     */
    void build() override {
        setElementPosition(100, 60);
        setElementSize(_width - 2 * timelineX, 6);
    }

    /**
     * @brief Ustawia pozycję elementu Timeline na ekranie.
     * @param x Współrzędna X.
     * @param y Współrzędna Y.
     * @return Wektor z nową pozycją.
     */
    Vector2 setElementPosition(unsigned x, unsigned y) override {
        timelineX = x;
        timelineY = y;
        return Vector2 { static_cast<float>(timelineX), static_cast<float>(timelineY) };
    }

    /**
     * @brief Ustawia rozmiar paska postępu.
     * @param x Szerokość.
     * @param y Wysokość.
     * @return Wektor z nowym rozmiarem.
     */
    Vector2 setElementSize(unsigned x, unsigned y) override {
        timelineWidth = x;
        timelineHeight = y;
        return Vector2{ static_cast<float>(timelineWidth), static_cast<float>(timelineHeight)};
    }

    /**
     * @brief Rysuje pasek postępu, znacznik oraz aktualny czas odtwarzania.
     *
     * Pasek jest rysowany w kolorze szarym, marker postępu w czerwonym.
     * Tekst z aktualnym czasem pojawia się nad paskiem.
     */
    void draw() override {
        DrawRectangle(timelineX, timelineY, timelineWidth, timelineHeight, GRAY);

        auto musicTime = GetMusicTimePlayed(_music);
        auto progressRatio = musicLength > 0 ? musicTime / musicLength : 0.0f;

        auto markerX = timelineX + (progressRatio * timelineWidth);
        DrawRectangle(markerX - 2, timelineY - 4, 4, timelineHeight + 8, RED);

        DrawText(TextFormat("%.2fs / %.2fs", musicTime, musicLength), timelineX, timelineY - 20, 20, LIGHTGRAY);
    }

    /**
     * @brief Destruktor klasy Timeline.
     */
    ~Timeline() override = default;
};

#endif // TIMELINE_H