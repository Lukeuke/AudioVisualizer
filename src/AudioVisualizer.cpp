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


    auto window = sf::RenderWindow(sf::VideoMode({800u, 600u}), "Audio Visualizer");
    window.setFramerateLimit(144);

    BottomBar bottomBar = BottomBar(&window);
    bottomBar.build();

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
