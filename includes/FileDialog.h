#ifndef FILEDIALOG_H
#define FILEDIALOG_H

#include <optional>
#include <string>

/**
* @class FileDialog
* @brief Klasa odpowiedzialna za dialog do wyboru plików
*
**/
class FileDialog {
public:
    static std::optional<std::string> openDialog(const char* fileExtension);
};

#endif //FILEDIALOG_H