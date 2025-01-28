#include "terminal_utils.hpp"

/**
 * @brief Pauses the terminal until the user presses ENTER and then clears the terminal screen.
 *
 * This function displays a message prompting the user to press ENTER to continue.
 * After the user presses ENTER, it clears the terminal screen. The method used
 * to clear the screen depends on the operating system:
 * - On Windows, it uses the "cls" command.
 * - On other systems, it uses the "clear" command.
 */
void flushTerminal() {
    std::string dummy;

    std::cout << "\nPressione ENTER para continuar...";
    std::cin.ignore();
    std::getline(std::cin, dummy);
    #ifdef _WIN32
        std::system("cls");
    #else
        std::system("clear");
    #endif
}

/**
 * @brief Clears the terminal screen.
 * 
 * This function clears the terminal screen to provide a clean interface for the user.
 * It uses platform-specific commands to clear the terminal:
 * - On Windows (_WIN32), it uses the "cls" command.
 * - On other platforms, it uses the "clear" command.
 */
void flushTerminalInGame() {
    #ifdef _WIN32
        std::system("cls");
    #else
        std::system("clear");
    #endif
}

/**
 * @brief Ensures that the save file exists.
 * 
 * This function checks if the save file located at "./saves/save.csv" exists.
 * If the file does not exist, it creates the file and writes the header line.
 */
void ensureSaveFileExists() {
    std::ifstream file("./saves/save.csv");
    if (!file.is_open()) {
        std::ofstream saveFile("./saves/save.csv");
        saveFile << "Id,Name,Nickname,TotalWins,WinsTTT,WinsLig4,WinsReversi,TotalLoses,LosesTTT,LosesLig4,LosesReversi\n";
        saveFile.close();
    }
    file.close();
}
