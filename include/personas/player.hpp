#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "persona.hpp"

class Player: public Persona  {

    public:
        Player();
        Player(std::string name, std::string nickname);


        ~Player();

};


#endif