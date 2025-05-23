cmake_minimum_required(VERSION 3.29)
project(AudioVisualizer LANGUAGES C CXX)

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

FetchContent_Declare(nfd
        GIT_REPOSITORY https://github.com/mlabbe/nativefiledialog.git
        GIT_TAG master
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM
)
FetchContent_MakeAvailable(nfd)

if(WIN32)
    set(NFD_PLATFORM_SRC ${nfd_SOURCE_DIR}/src/nfd_win.cpp)
elseif(APPLE)
    set(NFD_PLATFORM_SRC ${nfd_SOURCE_DIR}/src/nfd_cocoa.m)
else()
    set(NFD_PLATFORM_SRC ${nfd_SOURCE_DIR}/src/nfd_gtk.c)
endif()

add_library(nfd STATIC
        ${nfd_SOURCE_DIR}/src/nfd_common.c
        ${NFD_PLATFORM_SRC}
)

target_include_directories(nfd PUBLIC ${nfd_SOURCE_DIR}/src/include)

# Linux: link z GTK3
if(UNIX AND NOT APPLE)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
    target_include_directories(nfd PUBLIC ${GTK3_INCLUDE_DIRS})
    target_link_libraries(nfd PUBLIC ${GTK3_LIBRARIES})
endif()
#endregion

# Executable
add_executable(AudioVisualizer
        src/main.cpp
        includes/AudioVisualizer.h
        src/AudioVisualizer.cpp
        src/FileDialog.cpp
        src/BottomBar.cpp
)

target_compile_features(AudioVisualizer PRIVATE cxx_std_17)

# Link libraries
target_link_libraries(AudioVisualizer PRIVATE
        SFML::Graphics
        SFML::Audio
        CLI11::CLI11
        nfd
)
