cmake_minimum_required(VERSION 3.29)
project(AudioVisualizer)

set(CMAKE_CXX_STANDARD 20)

add_executable(AudioVisualizer src/main.cpp
        includes/AudioVisualizer.h
        src/AudioVisualizer.cpp
)
