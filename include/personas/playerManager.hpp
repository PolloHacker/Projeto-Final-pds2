#ifndef PLAYER_MANAGER_HPP
#define PLAYER_MANAGER_HPP

#include <vector>
#include <string>

#include "player.hpp"
#include "exceptions.hpp"



class PlayerManager {
    private:
        std::vector<Player> players;
        int num_players;

    public:

        PlayerManager();

        void removePlayer(std:: string nickname);

        void addPlayer(const std::string name, const std::string nickname, Stats stats);

        void addPlayer(const std::string name, const std::string nickname);

        void printPlayer(const std::string nickname);

        void loadPlayers(const std::string filename);

        bool readPlayerFromFile(std::istringstream &ss, std::string &id, std::string &name, std::string &nickname,
                                std::string &totalWins, std::string &winsTTT, std::string &winsLig4, std::string &winsReversi,
                                std::string &totalLoses, std::string &losesTTT, std::string &losesLig4, std::string &losesReversi);

        std::vector<Player>::iterator getPlayer(const std::string nickname);

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