//
// Created by Luuqe on 29.05.2025.
//

#ifndef SIDEBAR_H
#define SIDEBAR_H

#pragma once

#include <string.h>
#include <vector>

#include "raylib.h"
#include "GuiElement.h"
/**
 * @class Sidebar
 * @brief Element GUI wyświetlający listę plików audio dziedziczący po klasie abstrakcyjnej GuiElement
 */
class Sidebar final : public GuiElement {
    Rectangle barRect;                      ///< Prostokąt 
    Color barColor;                         ///< Pole koloru
    std::vector<std::string> audioFiles;    ///< Lista plików audio
    Font customFont;                        ///< Niestandardowa czcionka

public:
    /**
     * @brief konstruktor parametryczny klasy Sidebar odpowiedzialny za wstępną konfigurację elementu
     * @param parentWidth szerokość elementu nadrzędnego
     * @param parentHeight wysokość elementu 
     * @param fileNames lista nazw plikow
     */
    Sidebar(unsigned parentWidth, unsigned parentHeight, const std::vector<std::string> &fileNames)
        : GuiElement(parentWidth, parentHeight), audioFiles(fileNames) {
        size = setElementSize(parentWidth, parentHeight);
        position = setElementPosition(0.0f, 0.0f);  ///< Ustawienie pozycji na lewy górny róg

        /*barRect = { position.x, position.y, size.x, size.y };
        barColor = { 64, 64, 64, 255 }*/;

        customFont = LoadFont("assets/fonts/OpenSans-Regular.ttf"); ///< załadowanie niestandardowej czcionki
    }

    /**
     * Obowiązkowe nadpisanie metody build
     */
    void build() override {
        // TODO: Add elements to sidebar
    }
    /**
     * @brief nadpisanie metody draw()
     */
    void draw() override {
        DrawRectangleRec(barRect, barColor);    ///< narysowanie prostokątu o określonym rozmiarze, pozycji oraz kolorze

        constexpr float padding = 10.0f;        ///< ustawienie marginesu wewnętrznego na 10
        float textY = position.y + padding;     ///< wstawienie tekstu aplikując margines wewnętrzny

        for (const auto& file : audioFiles) {   ///< iteracja przez każdy plik audio
            constexpr int fontSize = 16;        ///< ustawienie rozmiaru czcionki na 16
            if (textY + fontSize > position.y + size.y) break;  ///< sprawdzenie czy tekst wychodzi poza ramkę, przerwanie listowania jeśli tak jest

            DrawText(file.c_str(), position.x + padding, textY, 20, WHITE); ///< wstawianie nazwy każdego pliku jako biały text

            // DrawTextEx(customFont, file.c_str(), { position.x + padding, textY }, 20, 2, WHITE);
            textY += fontSize + 6;              ///< zwiększenie rozmiaru tekstu o 6 względem rozmiaru czcionki
        }
    }
    /**
     * @brief nadpisanie dekonstruktora klasy GuiElement
     * wyłącza czcionkę z obsługi???
     */
    ~Sidebar() override {
        UnloadFont(customFont);
    }

private:
    /**
     * @brief nadpisanie metody klasy GuiElement setElementSize
     */
    Vector2 setElementSize(unsigned x, unsigned y) override {
        return { static_cast<float>(x) * 0.15f, static_cast<float>(y) };  // ustawienie rozmiaru elementu na 15% szerokości okna i 100% wysokości okna
    }
    /**
     * @brief nadpisanie metody klasy GuiElement setElementPosition
     */
    Vector2 setElementPosition(unsigned x, unsigned y) override {
        return { static_cast<float>(x), static_cast<float>(y) };  // ustawienie pozycji elementu na lewy górny róg
    }
};

#endif //SIDEBAR_H
