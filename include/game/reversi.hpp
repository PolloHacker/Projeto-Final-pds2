#ifndef REVERSI_HPP
#define REVERSI_HPP

#include "game.hpp"

class Reversi: public Game  {

    public:

        Reversi();

        void readMove() override;

        void validateMove(int row, int col);

        void makeMove();

        int isGameFinished() override;

        void printBoard() override;
};

#endif