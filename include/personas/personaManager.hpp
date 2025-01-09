#ifndef PERSONA_MANAGE_HPP
#define PERSONA_MANAGE_HPP

#include <vector>
#include "persona.hpp"
#include <string>


/**
 * @brief 
 * 
 */
class PersonaManager {
    private:
        std::vector<Persona> personas;
        static int num_personas;

    public:

        PersonaManager();

        void removePersona(std:: string nickname);

        void addPersona(std::string name, std::string nickname);

        void listPersonas();

        void updatePersonas();
        
        void verifyPersona();

        void printTable();
       
        ~PersonaManager();
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