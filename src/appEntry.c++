#include "TTT.hpp"
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
            pm.loadPlayers("opa.cpp");
        }
        else if (cmd.find("CJ") != std::string::npos) {

        }
        else if (cmd.find("RJ") != std::string::npos) {

        }
        else if (cmd.find("LJ") != std::string::npos) {

        }
        else if (cmd.find("EP") != std::string::npos) {

        }
    }
    
    std::cout << "Obrigado por usar o sistema" << std::endl;

    return (0);
}