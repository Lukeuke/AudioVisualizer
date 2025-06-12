#pragma once
#include "raylib.h"

/**
 * @class GuiElement
 * @brief Klasa Bazowa dla kadego elementu GUI tego 
 * Klasa ta poprzez wymuszenie definicji metod build() oraz draw()
 * pozwala na uproszczenie konstruowania elementow graficznych
 * wskazującym aktualną pozycję oraz czasem odtwarzania.
 */
class GuiElement {
protected:
    Vector2 windowSize{};   ///< Rozmiar okna
    Vector2 size{};         ///< Rozmiar elementu
    Vector2 position{};     ///< Pozycja elementu
    /**
     * @brief Metoda virtualna służąca do ustawienia rozmiaru elementu
     * @param x Szerokość elementu
     * @param y Wysokość elementu
     */
    virtual Vector2 setElementSize(unsigned x, unsigned y) = 0;
    /**
     * @brief Metoda virtualna służąca do ustawienia elementu względem osi x oraz y
     * @param x Pozycja elementu względem osi x
     * @param y Pozycja elementu względem osi y
     */
    virtual Vector2 setElementPosition(unsigned x, unsigned y) = 0;
public:
    /**
     * @brief Konstruktor parametryczny klasy GuiElement.
     * @param screenWidth Szerokość ekranu
     * @param screenHeight Wysokość ekranu
     */
    GuiElement(const unsigned screenWidth, const unsigned screenHeight) {
        windowSize = {static_cast<float>(screenWidth), static_cast<float>(screenHeight) };
    }
    /**
     * @brief Wirtualny Deskrutor zapewniający odpowiednie usuwanie obiektów klas pochodnych
     */
    virtual ~GuiElement() = default;
    /**
     * @brief Wirtualna metoda odpowiedzialna za konfigurację, inicjalizację komponentu  
     */
    virtual void build() = 0;
    /**
     * @brief Wirtualna metoda odpowiedzialna za narysowanie elementu na ekranie
     */
    virtual void draw() = 0;
};
