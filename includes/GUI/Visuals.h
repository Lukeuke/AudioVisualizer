#ifndef VISUALS_H
#define VISUALS_H

#include "GuiElement.h"
#include "raylib.h"
#include "../external/SimpleFFT.h"

/**
 * @class Visuals
 * @brief Klasa odpowiedzialna za wizualizację audio (FFT) w czasie rzeczywistym.
 *
 * Visuals wyświetla dynamiczną wizualizację dźwięku odtwarzanego z obiektu Music,
 * używając transformacji Fouriera (FFT) do analizy częstotliwości.
 */
class Visuals final : public GuiElement {
    Music _music;              ///< Streamowany obiekt muzyczny
    float* _samples;           ///< Tablica próbek audio (float), załadowana z pliku WAV
    unsigned int _sampleCount; ///< Liczba ramek audio
    unsigned int _channels;    ///< Liczba kanałów (1 = mono, 2 = stereo)
    unsigned int _sampleRate;  ///< Częstotliwość próbkowania (np. 44100 Hz)
    bool _debug;               ///< Flaga trybu debugowania (opcjonalna)

public:
    /**
     * @brief Konstruktor klasy Visuals.
     *
     * Wczytuje plik WAV, zapisuje jego próbki i przygotowuje dane do wizualizacji.
     *
     * @param screenWidth Szerokość okna aplikacji.
     * @param screenHeight Wysokość okna aplikacji.
     * @param music Obiekt Music do odtwarzania.
     * @param filename Ścieżka do pliku WAV zawierającego dane audio.
     * @param bottomBarHeight Wysokość dolnego paska GUI (dla przesunięcia wizualizacji).
     */
    Visuals(unsigned screenWidth, unsigned screenHeight, const Music &music, const char* filename, const float bottomBarHeight)
        : GuiElement(screenWidth, screenHeight - bottomBarHeight + 5) {

        const Wave wave = LoadWave(filename);   ///< Załaduj dane WAV do pamięci
        _sampleCount = wave.frameCount;         ///< Ilość ramek audio
        _channels = wave.channels;              ///< Liczba kanałów (mono/stereo)
        _sampleRate = wave.sampleRate;          ///< Częstotliwość próbkowania

        _samples = LoadWaveSamples(wave);       ///< Wskaźnik na próbki audio
        _music = music;                         ///< Przypisanie strumienia muzyki
        UnloadWave(wave);                       ///< Zwolnienie pamięci obiektu Wave
    }

    /**
     * @brief Destruktor klasy Visuals.
     *
     * Zwalnia pamięć zajmowaną przez próbki audio i strumień muzyki.
     */
    ~Visuals() {
        UnloadMusicStream(_music);
        UnloadWaveSamples(_samples);
    }

    /**
     * @brief Rozpoczyna odtwarzanie muzyki.
     */
    void build() override {
        PlayMusicStream(_music);
    }

    /**
     * @brief Rysuje wizualizację audio w czasie rzeczywistym.
     *
     * Aktualizuje strumień muzyczny, przelicza FFT i rysuje słupki reprezentujące częstotliwości.
     */
    void draw() override {
        UpdateMusicStream(_music);
        if (!IsMusicStreamPlaying(_music)) return;

        // Ile sekund muzyka już zagrała w sekundach
        float played = GetMusicTimePlayed(_music);

        // Na ile ramek przekłada się czas odtwarzania
        size_t currentFrame = static_cast<size_t>(played * _sampleRate);

        // Oblicz przesunięcie w tablicy próbek (uwzględniając kanały)
        size_t offset = currentFrame * _channels;

        const int fftSize = 128; // Liczba próbek do analizy FFT

        // Jeżeli próbki wyjdą poza zakres, przerwij
        if (offset + fftSize * _channels >= _sampleCount * _channels) return;

        std::vector<float> segment;

        // Wyciągnij fragment próbek tylko z 1 kanału (np. lewego)
        for (int i = 0; i < fftSize; ++i) {
            segment.push_back(_samples[offset + i * _channels]);
        }

        // Oblicz FFT i magnitudy (moduły)
        auto magnitudes = SimpleFFT::computeMagnitude(segment);

        // Skala wysokości słupków wizualizacji
        const float barHeightMagnitude = 0.2f;

        // Rysuj słupki wizualizacji na dole ekranu
        float barWidth = windowSize.x / magnitudes.size();
        for (size_t i = 0; i < magnitudes.size(); ++i) {
            float barHeight = magnitudes[i] * barHeightMagnitude * windowSize.y;
            DrawRectangle(i * barWidth, windowSize.y - barHeight, barWidth - 1, barHeight, BLUE);
        }

#if DEBUG
        // --- Debug ---
        const int fontSize = 20;
        Color debugColor = YELLOW;

        DrawText(TextFormat("Played time: %.2f s", played), 10, 10, fontSize, debugColor);
        DrawText(TextFormat("Sample count: %u", _sampleCount), 10, 10 + fontSize + 5, fontSize, debugColor);
        DrawText(TextFormat("Current offset: %zu", offset), 10, 10 + 2 * (fontSize + 5), fontSize, debugColor);
        DrawText(TextFormat("FFT size: %d", fftSize), 10, 10 + 3 * (fontSize + 5), fontSize, debugColor);
#endif
    }

    /**
     * @brief Nieużywana implementacja ustawiania rozmiaru elementu GUI.
     * @return Pusty wektor.
     */
    Vector2 setElementSize(unsigned, unsigned) override { return {}; }

    /**
     * @brief Nieużywana implementacja ustawiania pozycji elementu GUI.
     * @return Pusty wektor.
     */
    Vector2 setElementPosition(unsigned, unsigned) override { return {}; }

    /**
     * @brief Zwraca referencję do obiektu Music.
     * @return Referencja do muzyki.
     */
    Music& getMusic() { return _music; }
};

#endif //VISUALS_H
