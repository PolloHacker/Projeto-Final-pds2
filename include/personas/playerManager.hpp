#ifndef PLAYER_MANAGER_HPP
#define PLAYER_MANAGER_HPP

#include <vector>
#include "player.hpp"
#include <string>



class PlayerManager {
    private:
        std::vector<Player> players;
        static int num_players;

    public:

        PlayerManager();

        void removePlayer(std:: string nickname);

        void addPlayer(const std::string name, const std::string nickname, Stats stats);

        void printPlayer(const std::string nickname);

        void loadPlayers(const std::string filename);

        bool readPlayerFromFile(std::istringstream &ss, std::string &id, std::string &name, std::string &nickname,
                                std::string &totalWins, std::string &winsTTT, std::string &winsLig4, std::string &winsReversi,
                                std::string &totalLoses, std::string &losesTTT, std::string &losesLig4, std::string &losesReversi);

        void updatePlayer();
        
        bool verifyPlayer(const std::string nickname);

        std::vector<Player>::iterator getPlayer(const std::string nickname);

        void printTable();

       
        ~PlayerManager();
};

int PlayerManager::num_players = 0;

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