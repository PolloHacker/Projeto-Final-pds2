#ifndef TTT_HPP
#define TTT_HPP

#include <iostream>

#include "game.hpp"

class TTT : public Game {

    public:
        
        TTT();

        void readMove();

        bool isGameFinished();

        void validadeMove(int row, int col);

        void printBoard();
};

#endif