#include <iostream>
#include "exec_utils.hpp"


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

void ExecUtils::listFilesInDirectory(const std::string& path) {
    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        std::cout << entry.path().filename().string() << std::endl;
    }
}

void ExecUtils::handleLoadPlayers(PlayerManager &pm) {
    std::string path = "./path_to_directory"; // specify the path to the directory
    std::string filename;

    ExecUtils::listFilesInDirectory(path);

    std::cout << "Digite o nome do arquivo a ser carregado: ";
    std::cin >> filename;
    pm.loadPlayers(path + "/" + filename);
}

void ExecUtils::handleCreatePlayer(PlayerManager &pm) {
    std::string nickname, name;

    std::cout << "Digite o apelido e o nome do jogador: ";
    std::cin >> nickname >> name;
    pm.addPlayer(name, nickname);
}

void ExecUtils::handleRemovePlayer(PlayerManager &pm) {
    std::string nickname;

    std::cout << "Digite o apelido do jogador a ser removido: ";
    std::cin >> nickname;
    pm.removePlayer(nickname);
}

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
