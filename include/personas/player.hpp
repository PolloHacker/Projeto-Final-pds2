#ifndef PERSONA_HPP
#define PERSONA_HPP

#include <string>
#include "stats.hpp"

class Player {
    private:
        int _id;
        std::string _nickname;
        std::string _name;
        Stats _stats;

        static int num_players;

    public:

        Player(std::string nickname, std::string name);

        int getId() const;
        std::string getNickname() const;
        std::string getName() const;
        Stats getStats() const;   
        void setNickname(std::string nickname);
        void setName(std::string name);

        friend std::ostream& operator<<(std::ostream& os, const Player& player);

};

#endif