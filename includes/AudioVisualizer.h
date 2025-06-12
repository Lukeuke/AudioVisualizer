//
// Created by Luuqe on 12.05.2025.
//

#ifndef AUDIOVISUALIZER_H
#define AUDIOVISUALIZER_H

#include <optional>
#include <string>
#include "raylib.h"

/// @brief Bazowa klasa całego programu odpowiadająca za wizualizację dźwięku.
class AudioVisualizer {
    std::optional<std::string> _source;         ///< Ścieżka do źródła audio (opcjonalna).
    unsigned int _volume = 100;                 ///< Głośność początkowa (0–100).
    unsigned int _width = 1280, _height = 720;  ///< Wymiary okna aplikacji.
    Font _customFont{};                         ///< Własna czcionka używana do renderowania tekstu.
    bool _paused = false;                       ///< Flaga informująca, czy muzyka jest zapauzowana.

public:
    /// @brief Główna metoda uruchamiająca program.
    void run();

    /// @brief Zmienia głośność odtwarzanego utworu.
    /// @param music Referencja do obiektu muzyki.
    /// @param newVolume Nowa wartość głośności (0.0–1.0).
    void changeVolume(Music &music, float newVolume);

    /// @brief Ustawia źródło audio.
    /// @param source Opcjonalna ścieżka do pliku audio.
    /// @return Wskaźnik do bieżącego obiektu (dla łańcuchowania metod).
    AudioVisualizer *withSource(const std::optional<std::string> &source);

    /// @brief Ustawia początkową głośność.
    /// @param volume Wartość głośności (0–100).
    /// @return Wskaźnik do bieżącego obiektu (dla łańcuchowania metod).
    AudioVisualizer *withVolume(const unsigned int &volume);

    /// @brief Ustawia rozmiar okna aplikacji.
    /// @param width Szerokość okna.
    /// @param height Wysokość okna.
    /// @return Wskaźnik do bieżącego obiektu (dla łańcuchowania metod).
    AudioVisualizer *windowSize(const unsigned int &width, const unsigned int &height);

private:
    /// @brief Obsługuje stan pauzy muzyki.
    /// @param music Referencja do obiektu muzyki.
    void handleMusicPause(const Music &music);

    /// @brief Rysuje ekran informujący o zapauzowanej muzyce.
    void drawMusicPaused() const;
};

#endif // AUDIOVISUALIZER_H