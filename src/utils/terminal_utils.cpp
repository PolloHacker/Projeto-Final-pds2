#include "terminal_utils.hpp"

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

void flushTerminalInGame() {
    #ifdef _WIN32
        std::system("cls");
    #else
        std::system("clear");
    #endif
}

void ensureSaveFileExists() {
    std::ifstream file("./saves/save.csv");
    if (!file.is_open()) {
        std::ofstream saveFile("./saves/save.csv");
        saveFile << "Id,Name,Nickname,TotalWins,WinsTTT,WinsLig4,WinsReversi,TotalLoses,LosesTTT,LosesLig4,LosesReversi\n";
        saveFile.close();
    }
    file.close();
}
