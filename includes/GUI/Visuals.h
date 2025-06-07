#ifndef VISUALS_H
#define VISUALS_H

#include "GuiElement.h"
#include "raylib.h"
#include "../external/SimpleFFT.h"

class Visuals final : public GuiElement {
    Music _music;              // Obiekt streamowanego dźwięku
    float* _samples;           // Wskaźnik na próbki audio załadowane do pamięci
    unsigned int _sampleCount; // Liczba ramek (próbek)
    unsigned int _channels;    // Liczba kanałów (np. 2 dla stereo)
    unsigned int _sampleRate;  // Częstotliwość próbkowania (np. 44100 Hz)
    bool _debug;

public:
    Visuals(unsigned screenWidth, unsigned screenHeight, const Music &music, const char* filename, const float bottomBarHeight)
        : GuiElement(screenWidth, screenHeight - bottomBarHeight + 5) {

        const Wave wave = LoadWave(filename);   // Załaduj dane WAV do pamięci
        _sampleCount = wave.frameCount;   // Ile jest ramek
        _channels = wave.channels;        // Ile jest kanałów
        _sampleRate = wave.sampleRate;    // Częstotliwość próbkowania

        _samples = LoadWaveSamples(wave); // Załaduj wskaźnik na próbki (float[])
        _music = music;                   // Przypisz stream muzyki, żeby móc go kontrolować i aktualizować
        UnloadWave(wave);                 // Zwolnij Wave, bo próbki są osobno
    }

    ~Visuals() {
        // Zwolnij pamięć
        UnloadMusicStream(_music);
        UnloadWaveSamples(_samples);
    }

    void build() override {
        PlayMusicStream(_music);
    }

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

    Vector2 setElementSize(unsigned, unsigned) override { return {}; }
    Vector2 setElementPosition(unsigned, unsigned) override { return {}; }

    Music& getMusic() { return _music; }
};

#endif //VISUALS_H
