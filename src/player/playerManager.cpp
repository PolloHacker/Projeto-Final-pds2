#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

#include "playerManager.hpp"
#include "string_utils.hpp"

PlayerManager::PlayerManager() {
    this->players = std::vector<Player>();
    this->num_players = 0;
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

            try {
                this->addPlayer(name, nickname, stats);
            } catch (PlayerAlreadyExistsException &e) {
                std::cerr << "Error adding player: " << e.what() << std::endl;
            }
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
    try {
        this->players.erase(this->getPlayer(nickname));
        this->num_players--;
    } catch (PlayerNotInListException &e) {
        throw InexistentPlayerException();
    }
}

void PlayerManager::addPlayer(const std::string name, const std::string nickname, Stats stats) {
    if (StringUtils::IsInvalidNickname(nickname) || StringUtils::IsInvalidName(name)) {
        throw InvalidInputException("Name/Nickname");
    }
    try {
        this->getPlayer(nickname);
        throw PlayerAlreadyExistsException();
    } catch (PlayerNotInListException &e) {
        this->players.emplace_back(this->num_players++, name, nickname, stats);
    }
}

void PlayerManager::addPlayer(const std::string name, const std::string nickname) {
    try {
        this->addPlayer(name, nickname, Stats());
    } catch (PlayerAlreadyExistsException &e) {
        throw;    
    }
}

std::vector<Player>::iterator PlayerManager::getPlayer(const std::string nickname) {
    auto player =  std::find_if(this->players.begin(), this->players.end(), 
        [nickname](const Player &el) {
            return el.getNickname() == nickname; 
        }
    );

    if (player == this->players.end()) {
        throw PlayerNotInListException();
    }
    return player;
}

void PlayerManager::printTable() {
    std::cout << "Id\tNickname\tName\tTotal Wins\tWins TTT\tWins Lig4\tWins Reversi\tTotal Loses\tLoses TTT\tLoses Lig4\tLoses Reversi" << std::endl;
    for (auto &player : this->players) {
        std::cout << player.getId() << "\t" << player.getNickname() << "\t" << player.getName() << "\t" << player.getStats().TotalWins
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

int PlayerManager::getPlayerCount() {
    return PlayerManager::num_players;
}


PlayerManager::~PlayerManager() {
    this->players.clear();
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