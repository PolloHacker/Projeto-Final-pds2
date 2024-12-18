#ifndef PERSONA_HPP
#define PERSONA_HPP

#include <string>
#include <stats.hpp>

class Persona {
    private:
        int _id;
        std::string _name;
        Stats _stats;

        static int num_personas;

    public:

        Persona(std::string name): _stats(), _name(name), _id(this->num_personas++) {}

        int getId();
        std::string getName();
        Stats getStats();

        void setName(std::string name);

};

#endif