#include <persona.hpp>

int Persona::getId() {
    return this->_id;
}

std::string Persona::getName() {
    return this->_name;
}

Stats Persona::getStats() {
    return this->_stats;
}

void Persona::setName(std::string name) {
    if (name.length() <= 0) return;
    this->_name = name;
}