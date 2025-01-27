#ifndef PERSONA_HPP
#define PERSONA_HPP

#include <string>
#include "stats.hpp"
#include "exceptions.hpp"

class Player {
    private:
        int _id;
        std::string _name;
        std::string _nickname;
        Stats _stats;

        void updateGameStats(char game, bool isWin);

    public:

        Player(int id, std::string name, std::string nickname, Stats stats);
        Player(int id, std::string name, std::string nickname);

        int getId() const;

        std::string getNickname() const;

        std::string getName() const;

        void setNickname(std::string nickname);

        void setName(std::string name);

        Stats getStats() const;

        void updateStats(char result, char game);

        friend std::ostream& operator<<(std::ostream& os, const Player& player);

};

#endif