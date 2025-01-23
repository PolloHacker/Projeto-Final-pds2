#ifndef LIG4_HPP
#define LIG4_HPP

#include "game.hpp"


class Lig4 : public Game {
    
    public:
    
        Lig4(int rows, int cols);

        void readMove();

        void validateMove(int col);

        void makeMove(char symbol);

        int isGameFinished();

        void printBoard();
};

#endif