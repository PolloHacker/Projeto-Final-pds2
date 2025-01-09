#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "persona.hpp"

class Player: public Persona  {
    private:
        std::string name;

    public:
        Player();
        Player(std::string name, std::string nickname);


        ~Player();

};


#endif