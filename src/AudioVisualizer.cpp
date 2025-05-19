//
// Created by Luuqe on 12.05.2025.
//

#include "../includes/AudioVisualizer.h"

#include <iostream>
#include <ostream>
#include <SFML/Graphics.hpp>

void AudioVisualizer::run() const {
    std::cout << "Running AudioVisualizer..." << std::endl;

    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "Audio Visualizer");
    window.setFramerateLimit(144);

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
