#include "personaManager.hpp"
#include <iostream>
#include <fstream>
#include <string>

PersonaManager::PersonaManager() {
    

}

void PersonaManager::loadPersonas(const std::string filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string name, nickname;
        if (std::getline(ss, nickname, ',') && std::getline(ss, name, ',')) {
            addPersona(name, nickname);
        } else {
            std::cerr << "Error parsing line: " << line << std::endl;
        }
    }

    file.close();
}

void PersonaManager::removePersona(const std::string nickname) {
    
}

void PersonaManager::addPersona(const std::string name, const std::string nickname, Stats stats = Stats()) {
    
}

void PersonaManager::listPersonas() {
    
}

bool PersonaManager::verifyPersona(const std::string nickname) {
    if(std::find(personas.begin(), personas.end(), nickname) != personas.end()){
        return true;    
    }
    else{
        return false;   
    }

}

void PersonaManager:: printTable() {
    

}

PersonaManager::~PersonaManager() {
    
}



/*
CADASTRO:
CJ <Apelido> <Nome> (obs. Considere que <Apelido> é composto por uma única palavra)
Jogador <Apelido> cadastrado com sucesso
ERRO: dados incorretos
ERRO: jogador repetido

REMOVER:
RJ <Apelido>
Jogador <Apelido> removido com sucesso
ERRO: jogador inexistente

LISTAGEM:
LJ [A|N]
<Apelido> <Nome>
REVERSI - V: <#vitorias> D: <#derrotas>
LIG4 - V: <#vitorias> D: <#derrotas>
VELHA - V: <#vitorias> D: <#derrotas>
*/