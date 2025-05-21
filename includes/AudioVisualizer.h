//
// Created by Luuqe on 12.05.2025.
//

#ifndef AUDIOVISUALIZER_H
#define AUDIOVISUALIZER_H
#include <optional>
#include <string>

class AudioVisualizer {
    std::optional<std::string> _source;
    unsigned int _volume = 0;
    unsigned int _width = 800, _height = 600;
public:
    void run() const;

    AudioVisualizer *withSource(const std::optional<std::string> &source);
    AudioVisualizer *withVolume(const unsigned int &volume);
    AudioVisualizer *windowSize(const unsigned int &width, const unsigned int &height);
};

#endif //AUDIOVISUALIZER_H
