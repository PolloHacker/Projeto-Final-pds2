#include "exec_utils.hpp"

/**
 * @brief Prints the banner with available commands for the system.
 */
void ExecUtils::PrintBanner() {
    std::cout << 
    "+---------------------------Trabalho---------------------------+\n" <<
    "+ Comandos:                                                    +\n" <<
    "+ CA <nome_do_arquivo.csv> - Carrega execucoes anteriores      +\n" <<
    "+ CJ <apelido> <nome> - Criar jogador                          +\n" <<
    "+ RJ <apelido> - Remover jogador                               +\n" <<
    "+ LJ (A|N|C) - Listar jogadores                                +\n" <<
    "+ EP <Jogo: (R|L|V)> <apelido j1> <apelido j2> - Jogar um jogo +\n" <<
    "+ FS - Finalizar sistema                                       +\n" <<
    "+--------------------------------------------------------------+" << std::endl;
}

/**
 * @brief Lists all files in the specified directory.
 * 
 * @param path The path to the directory whose files are to be listed.
 */
void ExecUtils::listFilesInDirectory(const std::string& path) {
    DIR* dir;
    struct dirent* ent;
    if ((dir = opendir(path.c_str())) != nullptr) {
        while ((ent = readdir(dir)) != nullptr) {
            if (ent->d_type == DT_REG) { // Only list regular files
                std::cout << ent->d_name << std::endl;
            }
        }
        closedir(dir);
    } else {
        throw ("Could not open directory");
    }
}

/**
 * @brief Handles the loading of players from a specified file.
 * 
 * @param pm Reference to the PlayerManager instance where the players will be loaded.
 */
void ExecUtils::handleLoadPlayers(PlayerManager &pm) {
    std::string path = "./input"; // specify the path to the directory
    std::string filename;

    ExecUtils::listFilesInDirectory(path);

    std::cout << "Digite o nome do arquivo a ser carregado: ";
    std::cin >> filename;
    pm.loadPlayers(path + "/" + filename);
}

/**
 * @brief Handles the creation of a new player.
 * 
 * @param pm Reference to the PlayerManager instance where the new player will be added.
 */
void ExecUtils::handleCreatePlayer(PlayerManager &pm) {
    std::string nickname, name;

    std::cout << "Digite o apelido e o nome do jogador: ";
    std::cin >> nickname >> name;
    pm.addPlayer(name, nickname);
}

/**
 * @brief Handles the removal of a player from the PlayerManager.
 * 
 * @param pm Reference to the PlayerManager instance.
 */
void ExecUtils::handleRemovePlayer(PlayerManager &pm) {
    std::string nickname;

    std::cout << "Digite o apelido do jogador a ser removido: ";
    std::cin >> nickname;
    pm.removePlayer(nickname);
}

/**
 * @brief Handles the listing of players based on user input.
 * 
 * The user is prompted to enter:
 * - 'A' for listing by nickname, followed by the player's nickname.
 * - 'N' for listing by name, followed by the player's name.
 * - 'C' for a complete list of players.
 * 
 * @param pm Reference to the PlayerManager object that manages player information.
 * 
 */
void ExecUtils::handleListPlayers(PlayerManager &pm) {
    std::string type, player;

    std::cout << "Digite o tipo de listagem (A - Apelido, N - Nome, C - Lista completa): ";
    std::cin >> type;
    std::cout << "Digite o identificador do jogador: ";
    std::cin >> player;
    if (type == "A") {
        pm.printPlayerByNickname(player);
    } else if (type == "N") {
        pm.printPlayerByName(player);
    } else if (type == "C") {
        pm.printTable();
    } else {
        std::cout << "Tipo de listagem inválido." << std::endl;
    }
}

/**
 * @brief Handles the process of playing a game between two players.
 *
 * @param pm Reference to the PlayerManager object that manages the players.
 *
 * @throws InexistentPlayerException if one of the players does not exist in the PlayerManager.
 */
void ExecUtils::handlePlayGame(PlayerManager &pm) {
    char gameType;
    std::string player1, player2;

    std::cout << "Digite o tipo de jogo (R - Reversi, L - Lig4, V - Velha): ";
    std::cin >> gameType;
    std::cout << "Digite o apelido do jogador 1: ";
    std::cin >> player1;
    std::cout << "Digite o apelido do jogador 2: ";
    std::cin >> player2;

    try {
        Player& p1 = *pm.getPlayer(player1);
        Player& p2 = *pm.getPlayer(player2);

        std::unique_ptr<Game> game;

        if (gameType == 'R') {
            game = std::unique_ptr<Reversi>(new Reversi());
        } else if (gameType == 'L') {

            game = std::unique_ptr<Lig4>(new Lig4(6, 7));
        } else if (gameType == 'V') {

            game = std::unique_ptr<TTT>(new TTT());
        } else {
            std::cout << "Tipo de jogo inválido." << std::endl;
            return;
        }

        while (game->isGameFinished() == 'E') {
            game->printBoard();
            game->makeMove();
        }   

    } catch (const InexistentPlayerException &e) {
        std::cout << e.what() << std::endl;
    }
}
