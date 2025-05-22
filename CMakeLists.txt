cmake_minimum_required(VERSION 3.29)
project(AudioVisualizer LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)

#region Libraries
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.1
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM
)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(CLI11
        GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
        GIT_TAG v2.3.2
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM
)
FetchContent_MakeAvailable(CLI11)
#endregion

# Executable
add_executable(AudioVisualizer
        src/main.cpp
        includes/AudioVisualizer.h
        src/AudioVisualizer.cpp
        src/BottomBar.cpp
)

target_compile_features(AudioVisualizer PRIVATE cxx_std_17)

# Link libraries
target_link_libraries(AudioVisualizer PRIVATE
        SFML::Graphics
        SFML::Audio
        CLI11::CLI11
)
