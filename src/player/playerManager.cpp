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

void PlayerManager::loadPlayers(const std::string &filename) {
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
        PlayerData data;

        if (this->readPlayerFromFile(ss, data)) {

            Stats stats;
            stats.TotalWins = std::stoi(data.totalWins);
            stats.winsTTT = std::stoi(data.winsTTT);
            stats.winsLig4 = std::stoi(data.winsLig4);
            stats.winsReversi = std::stoi(data.winsReversi);
            stats.TotalLoses = std::stoi(data.totalLoses);
            stats.losesTTT = std::stoi(data.losesTTT);
            stats.losesLig4 = std::stoi(data.losesLig4);
            stats.losesReversi = std::stoi(data.losesReversi);

            try {
                this->addPlayer(data.name, data.nickname, stats);
            } catch (PlayerAlreadyExistsException &e) {
                std::cerr << "Error adding player: " << e.what() << std::endl;
            }
        } else {
            std::cerr << "Error parsing line: " << line << std::endl;
        }
    }

    file.close();
}

bool PlayerManager::readPlayerFromFile(std::istringstream &ss, PlayerData &data) {
    return this->readBasicFields(ss, data) && this->readStatsFields(ss, data);
}

bool PlayerManager::readBasicFields(std::istringstream &ss, PlayerData &data) {
    return this->readField(ss, data.id) && this->readField(ss, data.name) && this->readField(ss, data.nickname);
}

bool PlayerManager::readStatsFields(std::istringstream &ss, PlayerData &data) {
    return this->readField(ss, data.totalWins) && this->readField(ss, data.winsTTT) && this->readField(ss, data.winsLig4) &&
           this->readField(ss, data.winsReversi) && this->readField(ss, data.totalLoses) && this->readField(ss, data.losesTTT) &&
           this->readField(ss, data.losesLig4) && this->readField(ss, data.losesReversi);
}

bool PlayerManager::readField(std::istringstream &ss, std::string &field) {
    if (std::getline(ss, field, ',')) {
        return true;
    }
    return false;
}

void PlayerManager::removePlayer(const std::string &nickname) {
    try {
        this->players.erase(this->getPlayer(nickname));
        this->num_players--;
    } catch (PlayerNotInListException &e) {
        throw InexistentPlayerException();
    }
}

void PlayerManager::addPlayer(const std::string &name, const std::string &nickname, Stats stats) {
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

void PlayerManager::addPlayer(const std::string &name, const std::string &nickname) {
    try {
        this->addPlayer(name, nickname, Stats());
    } catch (PlayerAlreadyExistsException &e) {
        throw;    
    }
}

std::vector<Player>::iterator PlayerManager::getPlayer(const std::string &nickname) {
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

void PlayerManager::printPlayerByNickname(const std::string &nickname) {
    auto player = this->getPlayer(nickname);
    if (player != this->players.end()) {
        std::cout << *player;
    } else {
        std::cerr << "Error: player not found" << std::endl;
    }
}

void PlayerManager::printPlayerByName(const std::string &name) {
    auto player = std::find_if(this->players.begin(), this->players.end(), 
        [name](const Player &el) {
            return el.getName() == name; 
        }
    );

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