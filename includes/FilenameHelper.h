//
// Created by Luuqe on 29.05.2025.
//

#ifndef FILENAMEHELPER_H
#define FILENAMEHELPER_H

#pragma once

#include <string>

/**
 * @class FilenameHelper
 * @brief Klasa pomocnicza do pobierania nazwy pliku z pełnej ścieżki.
 *
 * Umożliwia wyodrębnienie samej nazwy pliku (z rozszerzeniem) z podanej ścieżki,
 * niezależnie od systemu operacyjnego (Windows, Linux, macOS).
 */
class FilenameHelper {
public:
    /**
     * @brief Zwraca nazwę pliku z podanej ścieżki.
     *
     * @param filePath Pełna ścieżka do pliku.
     * @return Nazwa pliku z rozszerzeniem (np. "audio.mp3").
     *
     * @note Obsługuje separatory ścieżek specyficzne dla różnych systemów operacyjnych.
     */
    static std::string getFileName(const std::string& filePath) {
#if defined(_WIN32)
        auto idx = filePath.find_last_of("\\");     ///< Dla Windowsa: szukamy ostatniego '\\'
#elif defined(__linux__) || defined(__APPLE__)
        auto idx = filePath.find_last_of("/");          ///< Dla Linuxa i macOS: szukamy ostatniego '/'
#else
        auto idx = std::string::npos;                   ///< Inny system: uznajemy brak separatora
#endif

        if (idx != std::string::npos) {
            return filePath.substr(idx + 1);
        }

        return filePath;
    }
};

#endif //FILENAMEHELPER_H
