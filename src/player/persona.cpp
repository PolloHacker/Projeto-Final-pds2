#include "persona.hpp"

Persona::Persona(std::string nickname) {
    
}

int Persona::getId() const { return this->_id; }

Stats Persona::getStats() const { return this->_stats; }

std::string Persona::getNickname() const { return this->_nickname; }

void Persona::setNickname(std::string nickname) {
    _nickname = nickname;
}