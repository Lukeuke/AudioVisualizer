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
public:
    void run() const;

    AudioVisualizer *withSource(std::optional<std::string> &source);
    AudioVisualizer *withVolume(const unsigned int &volume);
};

#endif //AUDIOVISUALIZER_H
