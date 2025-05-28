#include "raylib.h"
#include "../includes/AudioVisualizer.h"
#include "../includes/FileDialog.h"
#include "../includes/GUI/bottomBar/BottomBar.h"
#include "../includes/GUI/slider/Slider.h"
#include "raymath.h"

#include <iostream>

void AudioVisualizer::run() {

    std::cout << "Running AudioVisualizer..." << std::endl;

    InitWindow(_width, _height, "Audio Visualizer");
    SetTargetFPS(60);

    BottomBar bottomBar(_width, _height);
    bottomBar.build();

    Slider slider(_width, _height);
    slider.build();

#if defined(_WIN32)
    std::string fileName = "_support/input.wav";
#elif defined(__linux__) || defined(__APPLE__)
    std::string fileName = "../../_support/input.wav";
#endif

    if (_source.has_value()) {
        fileName = _source.value();
    }

    InitAudioDevice();
    const Sound sound = LoadSound(fileName.c_str());
    SetSoundVolume(sound, static_cast<float>(_volume) / 100.0f);
    PlaySound(sound);

    Vector2 mousePosition;
    bool mouseDown;

    while (!WindowShouldClose()) {
        ClearBackground(BLACK);

        mousePosition = GetMousePosition();
        mouseDown = IsMouseButtonDown(MOUSE_LEFT_BUTTON);

        float relX = slider.circlePosition.x;

        if(mouseDown) {
            if (
                    CheckCollisionPointCircle(mousePosition, slider.circlePosition, slider.circleRadius + 20)
                    || CheckCollisionPointRec(mousePosition, slider.sliderRect)
                    ) {
                relX = Clamp(mousePosition.x, slider.valueRange.x, slider.valueRange.y);
            }
        }
        slider.changeSliderPosition(relX);
        changeVolume(slider.returnNewVolume());

        BeginDrawing();

        bottomBar.draw();
        slider.draw();

        EndDrawing();
    }

    UnloadSound(sound);
    CloseAudioDevice();
    CloseWindow();
}

void AudioVisualizer::changeVolume(float newVolume) {
    _volume = static_cast<unsigned int>(newVolume * 100);
    SetMasterVolume(newVolume);
}

AudioVisualizer* AudioVisualizer::withSource(const std::optional<std::string>& source) {
    _source = source;
    return this;
}

AudioVisualizer* AudioVisualizer::withVolume(const unsigned int& volume) {
    _volume = volume;
    return this;
}

AudioVisualizer* AudioVisualizer::windowSize(const unsigned int& width, const unsigned int& height) {
    _width = width;
    _height = height;
    return this;
}
