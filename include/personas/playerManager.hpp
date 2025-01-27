#ifndef PLAYER_MANAGER_HPP
#define PLAYER_MANAGER_HPP

#include <iomanip>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

#include "terminal_utils.hpp"
#include "string_utils.hpp"
#include "player.hpp"
#include "exceptions.hpp"

class PlayerManager {
    private:
        std::vector<Player> players;
        int num_players;

        struct PlayerData {
            std::string id;
            std::string name;
            std::string nickname;
            std::string totalWins;
            std::string winsTTT;
            std::string winsLig4;
            std::string winsReversi;
            std::string totalLoses;
            std::string losesTTT;
            std::string losesLig4;
            std::string losesReversi;
        };

        bool readBasicFields(std::istringstream &ss, PlayerData &data);

        bool readStatsFields(std::istringstream &ss, PlayerData &data);

        bool readField(std::istringstream &ss, std::string &field);

        bool readPlayerFromFile(std::istringstream &ss, PlayerData &data);

        size_t getMaxNameLength();

        size_t getMaxNicknameLength();

    public:

        PlayerManager();

        void loadPlayers(const std::string &filename);

        void addPlayer(const std::string &name, const std::string &nickname, Stats stats);

        void addPlayer(const std::string &name, const std::string &nickname);

        void removePlayer(const std::string &nickname);

        void printPlayerByNickname(const std::string &nickname);

        void printPlayerByName(const std::string &name);

        std::vector<Player>::iterator getPlayer(const std::string &nickname);

        void updatePlayerStats(const std::string &nickname, char result);

        void exportPlayerData();

        void printTable();

        int getPlayerCount();

        ~PlayerManager();
};

#endif


/*
-Players (vetor).
-Num_Players.
-Cadastrar Player.
-Remover Player.
-Listar Players.
-Verificar Players.
-Atualizar Arquivo com Players.
-Printar Tabela de Classificação.
*/