#ifndef FILEDIALOG_H
#define FILEDIALOG_H

#include <optional>
#include <string>

// Class responsible for file dialogs
class FileDialog {
public:
    static std::optional<std::string> openDialog(const char* fileExtension);
};

#endif //FILEDIALOG_H