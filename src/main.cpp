//
// Created by Luuqe on 12.05.2025.
//

#include "../includes/AudioVisualizer.h"

#include <optional>
#include <CLI/CLI.hpp>

int main(const int argc, char** argv)
{
    CLI::App app{"Audio Visualizer"};

    std::optional<std::string> sourcePath;
    app.add_option("-s,--source", sourcePath, "Path to source file");

    unsigned int volume = 100;
    app.add_option("-V,--volume", volume, "Set volume (0-100)")
        ->check(CLI::Range(0, 100));

    unsigned int windowWidth = 1280;
    unsigned int windowHeight = 720;
    app.add_option("--width", windowWidth, "Window width")->check(CLI::Range(100, 3840));
    app.add_option("--height", windowHeight, "Window height")->check(CLI::Range(100, 2160));

    try {
        app.parse(argc, argv);
    } catch (const CLI::ParseError &e) {
        return app.exit(e);
    }

    AudioVisualizer audio;

    audio.withSource(sourcePath)
        ->windowSize(windowWidth, windowHeight)
        ->withVolume(volume)
        ->run();

    return 0;
}
