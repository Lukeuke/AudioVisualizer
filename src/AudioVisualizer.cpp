//
// Created by Luuqe on 12.05.2025.
//

#include "../includes/AudioVisualizer.h"
#include "GUI/bottomBar/BottomBar.h"

#include <iostream>
#include <ostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

void AudioVisualizer::run() const {

    std::cout << "Running AudioVisualizer..." << std::endl;

    auto window = sf::RenderWindow(sf::VideoMode({_width, _height}), "Audio Visualizer");
    window.setFramerateLimit(60);

    auto bottomBar = BottomBar(&window);
    bottomBar.build();

    // TODO: remove from prod this assignment :) (or feature?)
    std::string fileName = "_support/input.wav";
    if (_source.has_value()) {
        fileName = _source.value();
    }

    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(fileName)) {
        std::cerr << "Failed to load audio file" << std::endl;
        return;
    }
    sf::Sound sound(buffer);
    sound.setVolume(static_cast<float>(_volume));
    sound.play();

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear();
        bottomBar.draw();
        window.display();
    }
}

AudioVisualizer *AudioVisualizer::withSource(const std::optional<std::string> &source) {
    _source = source;
    return this;
}

AudioVisualizer *AudioVisualizer::withVolume(const unsigned int &volume) {
    _volume = volume;
    return this;
}

AudioVisualizer *AudioVisualizer::windowSize(const unsigned int &width, const unsigned int &height) {
    _width = width;
    _height = height;
    return this;
}
