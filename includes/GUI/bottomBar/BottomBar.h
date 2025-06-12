#pragma once
#include "../GuiElement.h"

/**
 * @class BottomBar
 * @brief Element GUI przedstawiający dolni pasek
 * Odpowiada on za narysowanie dolniego paska progresu na dolnej części ekranu
 */
class BottomBar final : public GuiElement {
    Rectangle barRect;  ///< deklaracja rozmiaru i umiejscowienia elementu
    Color barColor;     ///< deklaracja koloru elementu

public:
    /**
     * @brief Konstruktor klasy BottomBar
     * @param parentWidth   szerokość elementu nadrzędnego
     * @param parentHeight  wysokość elementu nadrzędnego
     */
    BottomBar(unsigned parentWidth, unsigned parentHeight)
        : GuiElement(parentWidth, parentHeight) {
        size = setElementSize(parentWidth, parentHeight);       ///< ustawienie jego 
        position = setElementPosition(0.0f, windowSize.y);      ///< ustawienie pozycji paska na sam dół okna

        barRect = { position.x, position.y, size.x, size.y };   ///< przypisanie danych odnośnie umiejscowienia i deklaracji do pola barRect
        barColor = { 64, 64, 64, 255 };                         ///< przypisanie barwy 
    }

    /**
     * @brief metoda zwracająca rozmiar elementu
     */
    Vector2 getSize() const {
        return size;
    }
    /**
     * @brief nadpisanie metody draw dziedziczonej z klasy GuiElement 
     */
    void build() override;
    /**
     * @brief nadpisanie metody wirtualnej draw dziedziczonej z klasy GuiElement 
     */
    void draw() override;
private:
    /**
     * @brief nadpisania metoda ustawiająca szerokość jako parametr x oraz wysokość jako 15% parametru y
     * @param x szerokość elementu
     * @param y wysokość elementu
     */
    Vector2 setElementSize(unsigned x, unsigned y) override {
        return { static_cast<float>(x), static_cast<float>(y) * 0.15f };
    }
    /**
     * @brief nadpisana metoda ustawiająca pozycję na osi x jako parametr x oraz pozycję na osi y jako różnica parametru y oraz wysokości elementu
     * @param x szerokość elementu
     * @param y wysokość elementu
     */
    Vector2 setElementPosition(unsigned x, unsigned y) override {
        return { static_cast<float>(x), static_cast<float>(y) - size.y };
    }
};
