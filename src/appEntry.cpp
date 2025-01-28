#include <algorithm>

#include "exec_utils.hpp"
#include "terminal_utils.hpp"
#include "playerManager.hpp"

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