cmake_minimum_required(VERSION 3.29)
project(AudioVisualizer LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.1
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(AudioVisualizer src/main.cpp
        includes/AudioVisualizer.h
        src/AudioVisualizer.cpp
)
target_compile_features(AudioVisualizer PRIVATE cxx_std_17)
target_link_libraries(AudioVisualizer PRIVATE SFML::Graphics)