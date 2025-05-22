#ifndef FILEDIALOG_H
#define FILEDIALOG_H

#include <nfd.h>
#include <string>

// Class responsible for file dialogs
class FileDialog {
public:
    static std::string openDialog(const char* fileExtension) ;
};

#endif //FILEDIALOG_H