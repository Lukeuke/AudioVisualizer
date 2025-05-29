//
// Created by Luuqe on 29.05.2025.
//

#ifndef FILENAMEHELPER_H
#define FILENAMEHELPER_H

#pragma once

#include <string>

class FilenameHelper {
public:
    static std::string getFileName(const std::string& filePath) {
#if defined(_WIN32)
        auto idx = filePath.find_last_of("\\");
#elif defined(__linux__) || defined(__APPLE__)
        auto idx = filePath.find_last_of("/");
#else
        auto idx = std::string::npos;
#endif

        if (idx != std::string::npos) {
            return filePath.substr(idx + 1);
        }

        return filePath;
    }
};


#endif //FILENAMEHELPER_H
