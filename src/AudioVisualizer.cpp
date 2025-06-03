#include "raylib.h"
#include "../includes/AudioVisualizer.h"
#include "../includes/FileDialog.h"
#include "../includes/FilenameHelper.h"
#include "../includes/GUI/bottomBar/BottomBar.h"
#include "../includes/GUI/slider/Slider.h"
#include "../includes/GUI/Sidebar.h"
#include "raymath.h"

#include <iostream>

#include "../includes/GUI/Timeline.h"

void AudioVisualizer::run() {

    std::cout << "Running AudioVisualizer..." << std::endl;

#if defined(_WIN32)
    std::string fileName = "_support/input.wav";
#elif defined(__linux__) || defined(__APPLE__)
    std::string fileName = "../../_support/input.wav";
#endif

    if (_source.has_value()) {
        fileName = _source.value();
    }

    InitWindow(_width, _height, "Audio Visualizer");
    SetTargetFPS(60);

    _customFont = LoadFont("assets/fonts/OpenSans-Regular.ttf");
    std::vector fileNames = {FilenameHelper::getFileName(fileName)};

    InitAudioDevice();
    Music music = LoadMusicStream(fileName.c_str());

    BottomBar bottomBar(_width, _height);
    bottomBar.build();

    Sidebar sidebar(_width, _height, fileNames);
    sidebar.build();

    Slider slider(_width, _height);
    slider.build();

    Timeline timeline(_width, music);
    timeline.build();

    SetMusicVolume(music, static_cast<float>(_volume) / 100.0f);
    PlayMusicStream(music);

    while (!WindowShouldClose()) {
        ClearBackground(BLACK);
        UpdateMusicStream(music);

        float relX = slider.circlePosition.x;

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePos = GetMousePosition();

            // handle volume
            if (
                    CheckCollisionPointCircle(mousePos, slider.circlePosition, slider.circleRadius + 20)
                    || CheckCollisionPointRec(mousePos, slider.sliderRect)
                    ) {
                relX = Clamp(mousePos.x, slider.valueRange.x, slider.valueRange.y);
            }

            // handle timeline change
            if (mousePos.y >= timeline.timelineY && mousePos.y <= timeline.timelineY + timeline.timelineHeight &&
            mousePos.x >= timeline.timelineX && mousePos.x <= timeline.timelineX + timeline.timelineWidth) {

                        float clickRatio = (mousePos.x - timeline.timelineX) / timeline.timelineWidth;
                        SeekMusicStream(music, clickRatio * timeline.musicLength);
            }
        }

        slider.changeSliderPosition(relX);
        changeVolume(music, slider.returnNewVolume());

        handleMusicPause(music);

        BeginDrawing();

        bottomBar.draw();
        sidebar.draw();
        slider.draw();
        drawMusicPaused();
        timeline.draw();

        EndDrawing();
    }

    UnloadMusicStream(music);
    CloseAudioDevice();
    CloseWindow();
}

void AudioVisualizer::changeVolume(Music &music, const float newVolume) {
    _volume = static_cast<unsigned int>(newVolume * 100);
    SetMusicVolume(music, newVolume);
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

void AudioVisualizer::handleMusicPause(const Music &music) {
    if (IsKeyPressed(KEY_SPACE)) {
        if (IsMusicStreamPlaying(music)) {
            _paused = true;
            PauseMusicStream(music);
        }
        else {
            _paused = false;
            ResumeMusicStream(music);
        }
    }
}

void AudioVisualizer::drawMusicPaused() const {
    if (_paused) {
        // overlay
        DrawRectangle(0, 0, _width, _height, Fade(BLACK, 0.6f));

        const auto pauseText = "PAUSED";
        constexpr auto fontSize = 50.0f;
        const auto textWidth = MeasureText(pauseText, fontSize);

        // align center
        float posX = (_width / 2) - (textWidth / 2);
        float posY = (_height / 2) - (fontSize / 2);

        // DrawTextEx(_customFont, pauseText, { posX, posY }, fontSize, 2, WHITE);
        DrawText(pauseText, posX, posY, fontSize, WHITE);
    }
}
