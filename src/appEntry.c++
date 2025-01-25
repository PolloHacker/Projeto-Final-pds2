#include "exec_utils.hpp"
#include "playerManager.hpp"

int main() {

    std::string cmd;
    PlayerManager pm;

    ExecUtils::PrintBanner();


    while(true) {
        std::cin >> cmd;

        if(cmd == "FS") {
            break;
        } 
        else if (cmd.find("CA") != std::string::npos) {
            ExecUtils::handleLoadPlayers(pm);
        }
        else if (cmd.find("CJ") != std::string::npos) {
            ExecUtils::handleCreatePlayer(pm);
        }
        else if (cmd.find("RJ") != std::string::npos) {
            ExecUtils::handleRemovePlayer(pm);
        }
        else if (cmd.find("LJ") != std::string::npos) {
            ExecUtils::handleListPlayers(pm);
        }
        else if (cmd.find("EP") != std::string::npos) {
            ExecUtils::handlePlayGame(pm);
        }
    }
    
    std::cout << "Obrigado por usar o sistema" << std::endl;

    return (0);
}