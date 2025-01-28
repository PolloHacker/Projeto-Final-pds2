#include <algorithm>

#include "exec_utils.hpp"
#include "terminal_utils.hpp"
#include "playerManager.hpp"

/**
 * @file appEntry.cpp
 * @brief Entry point for the application.
 *
 * This file contains the main function which serves as the entry point for the application.
 * It handles user commands to manage players and play the game.
 *
 * The following commands are supported:
 * - "FS": Finalize the system and exit the application.
 * - "CA": Load players from a save file.
 * - "CJ": Create a new player.
 * - "RJ": Remove an existing player.
 * - "LJ": List all players.
 * - "EP": Play the game.
 *
 * The commands are case-insensitive.
 *
 * @return int Returns 0 upon successful execution.
 */
int main() {

    std::string cmd;
    PlayerManager pm;

    bool hasLoadedPlayers = false;
    ensureSaveFileExists();

    while(true) {
        ExecUtils::PrintBanner();
        std::cout << "Digite seu comando: ";
        std::cin >> cmd;
        std::transform(cmd.begin(), cmd.end(), cmd.begin(),
               [](unsigned char c){ return std::toupper(c); });

        if(cmd == "FS") {
            break;
        } 
        else if (cmd.find("CA") != std::string::npos) {
            if (!hasLoadedPlayers) {
                ExecUtils::handleLoadPlayers(pm);
                hasLoadedPlayers = true;
                std::cout << "[!] - Jogadores carregados com sucesso" << std::endl;
            } else {
                std::cout << "[!] - Os jogadores já foram carregados" << std::endl;
            }
        }
        else if (cmd.find("CJ") != std::string::npos) {
            ExecUtils::handleCreatePlayer(pm);
            std::cout << "[!] - Jogador criado com sucesso" << std::endl;
        }
        else if (cmd.find("RJ") != std::string::npos) {
            ExecUtils::handleRemovePlayer(pm);
            std::cout << "[!] - Jogador removido com sucesso" << std::endl;
        }
        else if (cmd.find("LJ") != std::string::npos) {
            ExecUtils::handleListPlayers(pm);
        }
        else if (cmd.find("EP") != std::string::npos) {
            try {
                ExecUtils::handlePlayGame(pm);
            } catch(const InvalidInputException& e) {
                std::cerr << e.what() << '\n';
                ExecUtils::handlePlayGame(pm);
            }
            pm.exportPlayerData();
        }
        else {
            std::cout << "[X] - Comando inválido" << std::endl;
        }
        flushTerminal();
    }
    
    std::cout << "Obrigado por usar o sistema" << std::endl;

    return (0);
}