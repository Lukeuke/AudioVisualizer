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
    /**
     * @brief Otwiera systemowe okno dialogowe umożliwiające wybór pliku.
     *
     * @param fileExtension Rozszerzenie filtrowanych plików.
     * @return Ścieżka do wybranego pliku. Zwraca std::nullptr, jeśli użytkownik anulował wybór.
     */
    static std::optional<std::string> openDialog(const char* fileExtension);
};

#endif //FILEDIALOG_H