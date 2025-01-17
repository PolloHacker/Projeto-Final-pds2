#ifndef TTT_HPP
#define TTT_HPP

#include <iostream>

#include "game.hpp"

class TTT : public Game {

    public:
        
        TTT(int rows, int cols);

        void readMove();

        bool isGameFinished();

        void validadeMove();

        void printBoard();

        ~TTT();
};

#endif