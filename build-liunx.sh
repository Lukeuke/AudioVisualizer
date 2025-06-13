#!/bin/bash

if [ ! -d "./build" ] && [ ! -d "./cmake-build-debug" ]; then
    cmake -B build
    cmake --build build
else
    cmake --build build
fi

exePath="./build/bin/AudioVisualizer"

if [ -x "$exePath" ]; then
    "$exePath"
else
    echo "Executable not found or not executable: $exePath"
fi
