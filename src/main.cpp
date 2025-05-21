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

    try {
        app.parse(argc, argv);
    } catch (const CLI::ParseError &e) {
        return app.exit(e);
    }

    AudioVisualizer audio;
    audio.withSource(sourcePath)->withVolume(volume)->run();

    return 0;
}
