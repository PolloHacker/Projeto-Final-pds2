#ifndef TTT_HPP
#define TTT_HPP

#include <iostream>

#include "game.hpp"

class TTT : public Game {
    private:
        void validateMove(int row, int col);

        int checkLine(bool isRow);

        int checkRows();

        int checkColumns();

        int checkDiagonals();

    public:
        
        TTT();

        void readMove() override;

        void makeMove();

        int checkLine(bool isRow);

        int checkRows();

        int checkColumns();

        int checkDiagonals();

        char isGameFinished() override;

        //void printBoard() override;
};

#endif