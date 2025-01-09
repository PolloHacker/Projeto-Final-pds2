#ifndef PERSONA_MANAGE_HPP
#define PERSONA_MANAGE_HPP

#include <vector>
#include "persona.hpp"
#include <string>



class PersonaManager {
    private:
        std::vector<Persona> personas;
        static int num_personas;

    public:

        PersonaManager();

        void removePersona(std:: string nickname);

        void addPersona(const std::string name, const std::string nickname, Stats stats);

        void listPersonas();

        void loadPersonas(const std::string filename);

        void updatePersonas();
        
        bool verifyPersona(const std::string nickname);

        void printTable();
       
        ~PersonaManager();
};

int PersonaManager::num_personas = 0;

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