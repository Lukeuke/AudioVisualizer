//
// Created by Luuqe on 12.05.2025.
//

#include "../includes/AudioVisualizer.h"

#include <iostream>
#include <ostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

void AudioVisualizer::run() const {
    std::cout << "Running AudioVisualizer..." << std::endl;

    auto window = sf::RenderWindow(sf::VideoMode({800u, 600u}), "Audio Visualizer");
    window.setFramerateLimit(144);

    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("./_support/input.wav")) {
        std::cerr << "Failed to load audio file" << std::endl;
        return;
    }

    sf::Sound sound(buffer);
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
        window.display();
    }
}
