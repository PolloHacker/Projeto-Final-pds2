#include "playerManager.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

PlayerManager::PlayerManager() {
    this->players = std::vector<Player>();
}

void PlayerManager::loadPlayers(const std::string filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
    // Skip the header line
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string id, name, nickname, totalWins, winsTTT, winsLig4, winsReversi, totalLoses, losesTTT, losesLig4, losesReversi;

        if (this->readPlayerFromFile(ss, id, name, nickname, totalWins, winsTTT, winsLig4, 
                            winsReversi, totalLoses, losesTTT, losesLig4, losesReversi)) {

            Stats stats;
            stats.TotalWins = std::stoi(totalWins);
            stats.winsTTT = std::stoi(winsTTT);
            stats.winsLig4 = std::stoi(winsLig4);
            stats.winsReversi = std::stoi(winsReversi);
            stats.TotalLoses = std::stoi(totalLoses);
            stats.losesTTT = std::stoi(losesTTT);
            stats.losesLig4 = std::stoi(losesLig4);
            stats.losesReversi = std::stoi(losesReversi);

            this->addPlayer(name, nickname, stats);
        } else {
            std::cerr << "Error parsing line: " << line << std::endl;
        }
    }

    file.close();
}

bool PlayerManager::readPlayerFromFile(std::istringstream &ss, std::string &id,
                                       std::string &name, std::string &nickname, std::string &totalWins, std::string &winsTTT,
                                       std::string &winsLig4, std::string &winsReversi, std::string &totalLoses, std::string &losesTTT,
                                       std::string &losesLig4, std::string &losesReversi) {
    return std::getline(ss, id, ',') && std::getline(ss, name, ',') && std::getline(ss, nickname, ',') &&
           std::getline(ss, totalWins, ',') && std::getline(ss, winsTTT, ',') && std::getline(ss, winsLig4, ',') &&
           std::getline(ss, winsReversi, ',') && std::getline(ss, totalLoses, ',') && std::getline(ss, losesTTT, ',') &&
           std::getline(ss, losesLig4, ',') && std::getline(ss, losesReversi, ',');
}

void PlayerManager::removePlayer(const std::string nickname) {
    if (this->verifyPlayer(nickname)) {
        this->players.erase(this->getPlayer(nickname));
    }
}

void PlayerManager::addPlayer(const std::string name, const std::string nickname, Stats stats = Stats()) {
    if (this->verifyPlayer(nickname)) {
        std::cerr << "Error: nickname already exists" << std::endl;
        return;
    } else {
        this->players.emplace_back(name, nickname, stats);
    }
}

std::vector<Player>::iterator PlayerManager::getPlayer(const std::string nickname) {
    auto found_player = std::find_if(this->players.begin(), this->players.end(), [nickname](const Player &el)
                                      { return el.getNickname() == nickname; });

    return found_player;
}

bool PlayerManager::verifyPlayer(const std::string nickname) {
    return !((this->getPlayer(nickname) != this->players.end()) || nickname.find(" ") != std::string::npos);
}

void PlayerManager::printTable() {
    std::cout << "Nickname\tName\tTotal Wins\tWins TTT\tWins Lig4\tWins Reversi\tTotal Loses\tLoses TTT\tLoses Lig4\tLoses Reversi" << std::endl;
    for (auto &player : this->players) {
        std::cout << player.getNickname() << "\t" << player.getName() << "\t" << player.getStats().TotalWins
                  << "\t" << player.getStats().winsTTT << "\t" << player.getStats().winsLig4 << "\t"
                  << player.getStats().winsReversi << "\t" << player.getStats().TotalLoses << "\t"
                  << player.getStats().losesTTT << "\t" << player.getStats().losesLig4 << "\t"
                  << player.getStats().losesReversi << std::endl;
    }
}

void PlayerManager::printPlayer(const std::string nickname) {
    auto player = this->getPlayer(nickname);
    if (player != this->players.end()) {
        std::cout << *player;
    } else {
        std::cerr << "Error: player not found" << std::endl;
    }
}




/*
CADASTRO:
CJ <Apelido> <Nome> (obs. Considere que <Apelido> é composto por uma única palavra)
Jogador <Apelido> cadastrado com sucesso
ERRO: dados incorretos
ERRO: jogador repetido

REMOVER:
RJ <Apelido>
Jogador <Apelido> removido com sucesso
ERRO: jogador inexistente

LISTAGEM:
LJ [A|N]
<Apelido> <Nome>
REVERSI - V: <#vitorias> D: <#derrotas>
LIG4 - V: <#vitorias> D: <#derrotas>
VELHA - V: <#vitorias> D: <#derrotas>
*/