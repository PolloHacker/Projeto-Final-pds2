#ifndef TTT_HPP
#define TTT_HPP

#include <iostream>

#include "game.hpp"

class TTT : public Game {

    public:
        
        TTT();

        void readMove();

        int checkLine(bool isRow);

        int checkRows();

        int checkColumns();

        int checkDiagonals();

        bool isDraw();

        int isGameFinished();

        void validadeMove(int row, int col);

        void printBoard();
};

#endif