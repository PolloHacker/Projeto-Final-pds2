#ifndef LIG4_HPP
#define LIG4_HPP

#include "game.hpp"


class Lig4 : public Game {
    
    public:
    
        Lig4(int rows, int cols);

        void readMove() override;

        void validateMove(int col);

        void makeMove();

        int isGameFinished() override;
};

#endif