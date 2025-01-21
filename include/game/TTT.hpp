#ifndef TTT_HPP
#define TTT_HPP

#include <iostream>

#include "game.hpp"

class TTT : public Game {

    public:
        
        TTT();

        void readMove();

        void validadeMove(int row, int col);

        void makeMove(char symbol);

        int checkLine(bool isRow);

        int checkRows();

        int checkColumns();

        int checkDiagonals();

        int isGameFinished();

        void printBoard();
};

#endif