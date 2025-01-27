#include "exec_utils.hpp"

/**
 * @brief Prints the banner with available commands for the system.
 */
void ExecUtils::PrintBanner() {
    std::cout << 
    "+---------------------------Trabalho---------------------------+\n" <<
    "+ Comandos:                                                    +\n" <<
    "+ CA - Carrega execucoes anteriores                            +\n" <<
    "+ CJ - Criar jogador                                           +\n" <<
    "+ RJ - Remover jogador                                         +\n" <<
    "+ LJ - Listar jogadores                                        +\n" <<
    "+ EP - Jogar um jogo                                           +\n" <<
    "+ FS - Finalizar sistema                                       +\n" <<
    "+--------------------------------------------------------------+" << std::endl;
}

/**
 * @brief Handles the loading of players from the save file.
 * 
 * @param pm Reference to the PlayerManager instance where the players will be loaded.
 */
void ExecUtils::handleLoadPlayers(PlayerManager &pm) {
    pm.loadPlayers("./saves/save.csv");
}

/**
 * @brief Handles the creation of a new player.
 * 
 * @param pm Reference to the PlayerManager instance where the new player will be added.
 */
void ExecUtils::handleCreatePlayer(PlayerManager &pm) {
    std::string nickname = "";
    std::string name = "";

    std::cout 
        << "---------------------------------------\n"
        << "[!] Regras para nome de jogador       -\n"
        << "- Apenas letras e espaços             -\n"
        << "- Sem caracteres especiais ou numeros -\n"
        << "---------------------------------------\n"
        << "Digite o nome do jogador:" << std::endl;
    std::cin.ignore();
    std::getline(std::cin, name);
    while (StringUtils::IsInvalidName(name)) {
        std::cout << "Nome inválido.\nDigite o nome do jogador novamente: " << std::endl;
        std::getline(std::cin, name);
    }

    std::cout 
        << "---------------------------------------\n"
        << "[!] Regras para apelido de jogador    -\n"
        << "- Apenas letras e números             -\n"
        << "- Sem caracteres especiais ou espaços -\n"
        << "---------------------------------------\n"
        << "Digite o apelido do jogador:" << std::endl;
    std::getline(std::cin, nickname);
    while (StringUtils::IsInvalidNickname(nickname)) {
        std::cout << "Apelido inválido.\nDigite o apelido do jogador novamente: " << std::endl;
        std::getline(std::cin, nickname);
    }
    try {
        pm.addPlayer(name, nickname);
        pm.exportPlayerData();
    } catch (const InvalidInputException &e) {
        std::cout << e.what() << std::endl;
    } catch (const PlayerAlreadyExistsException &e) {
        std::cout << "Jogador já cadastrado" << std::endl;
    }
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
    try {
        pm.removePlayer(nickname);
        pm.exportPlayerData();
    } catch (const InexistentPlayerException &e) {
        std::cout << e.what() << std::endl;
        return;
    }
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
    if (type == "A") {
        std::cout << "Digite o apelido do jogador: ";
        std::cin >> player;
        pm.printPlayerByNickname(player);
    } else if (type == "N") {
        std::cout << "Digite o nome do jogador: ";
        std::cin.ignore();
        std::getline(std::cin, player);
        pm.printPlayerByName(player);
    } else if (type == "C") {
        pm.printTable();
    } else {
        std::cout << "[X] - Tipo de listagem inválido." << std::endl;
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
    char gameType, gameStatus = 'E';
    std::string player1, player2;
    std::unique_ptr<Game> game;

    std::cout << "Digite o tipo de jogo (R - Reversi, L - Lig4, V - Velha): ";
    std::cin >> gameType;

    while (gameType != 'R' && gameType != 'L' && gameType != 'V') {
        std::cout << "[X] - Tipo de jogo inválido." << std::endl;
        std::cout << "Digite o tipo de jogo (R - Reversi, L - Lig4, V - Velha): ";
        std::cin >> gameType;
    }
    
    if (gameType == 'R') {
        game = std::unique_ptr<Reversi>(new Reversi());
    } else if (gameType == 'L') {
        game = std::unique_ptr<Lig4>(new Lig4(6, 7));
    } else if (gameType == 'V') {
        game = std::unique_ptr<TTT>(new TTT());
    }


    std::cout << "Digite o apelido do jogador 1: ";
    std::cin >> player1;
    
    while (true) {
        try {
            *pm.getPlayer(player1);
            break;
        } catch (const PlayerNotInListException &e) {
            std::cout << "[X] - Jogador 1 não encontrado.\nDigite o apelido do jogador 1 novamente: ";
            std::cin >> player1;
        }
    }
    
    std::cout << "Digite o apelido do jogador 2: ";
    std::cin >> player2;

    while (true) {
        try {
            *pm.getPlayer(player2);
            break;
        } catch (const PlayerNotInListException &e) {
            std::cout << "[X] - Jogador 2 não encontrado.\nDigite o apelido do jogador 2 novamente: ";
            std::cin >> player2;
        }
    }

    std::cout 
        << "+---------------------------------+\n" 
        << "Iniciando o jogo\n" 
        << "Jogador 1 (X): " << player1 << " | "
        << "Jogador 2 (O): " << player2 << "\n"
        << "Jogador 1 começa\n"
        << std::endl;

    flushTerminal();
    while (gameStatus == 'E') {
        game->printBoard();
        game->makeMove();
        gameStatus = game->isGameFinished();
    }
    game->printBoard();
    std::cout << "O jogo acabou!" 
        << (gameStatus == 'D' ? " Empate!" : " O jogador " + (gameStatus == 'X' ? player1 : player2) + " venceu!\n")
        << "+---------------------------+\n" 
        << std::endl;
    
    pm.updatePlayerStats(player1, gameStatus == 'D' ? 'D' : (gameStatus == 'X' ? 'W' : 'L'));
    pm.updatePlayerStats(player2, gameStatus == 'D' ? 'D' : (gameStatus == 'O' ? 'W' : 'L'));

    pm.exportPlayerData();
}