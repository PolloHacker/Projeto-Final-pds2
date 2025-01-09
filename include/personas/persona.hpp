#ifndef PERSONA_HPP
#define PERSONA_HPP

#include <string>
#include "stats.hpp"

class Persona {
    private:
        int _id;
        std::string _nickname;
        Stats _stats;

        static int num_personas;

    public:

        Persona(std::string nickname): _stats(), _nickname(nickname), _id(this->num_personas++) {}

        int getId() const;
        std::string getNickname() const;
        Stats getStats() const;   
        void setNickname(std::string nickname);

};

#endif