#include "../includes/FileDialog.h"

#include <optional>
#include <string>
#include <nfd.h>

// openDialog method takes extension as an argument (for example wav, png),
// opens a system's file dialog for user to choose a file,
// and then returns file path - if the file was chosen, or nullptr if it was not
std::optional<std::string> FileDialog::openDialog(const char* fileExtension) {
    nfdchar_t* outPath = nullptr;

    const auto result = NFD_OpenDialog(
            fileExtension,
            nullptr,
            &outPath
            );

    if (result == NFD_OKAY) {
        std::string selectedFile(outPath);
        free(outPath);
        return selectedFile;
    }

    if (result == NFD_CANCEL) {
        return nullptr;
    }

    return nullptr;
}