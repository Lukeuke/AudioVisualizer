//
// Created by Luuqe on 12.05.2025.
//

#ifndef AUDIOVISUALIZER_H
#define AUDIOVISUALIZER_H
#include <optional>
#include <string>
#include "raylib.h"

// Bazowa klasa całego programu
class AudioVisualizer {
    std::optional<std::string> _source;
    unsigned int _volume = 100;
    unsigned int _width = 1280, _height = 720;
    Font _customFont{};
    bool _paused = false;
public:
    void run();
    void changeVolume(Music &music, float newVolume);

    // Wzorzec budowniczy
    AudioVisualizer *withSource(const std::optional<std::string> &source);
    AudioVisualizer *withVolume(const unsigned int &volume);
    AudioVisualizer *windowSize(const unsigned int &width, const unsigned int &height);
private:
    void handleMusicPause(const Music &music);
    void drawMusicPaused() const;
};

#endif //AUDIOVISUALIZER_H
