#ifndef LIG4_HPP
#define LIG4_HPP

#include "game.hpp"


class Lig4 : public Game {
    private:

        bool checkDirection(int row, int col, int rowDir, int colDir);

        void readMove() override;

    public:
    
        Lig4(int rows, int cols);

        void validateMove(int col);

        void makeMove();

        char isGameFinished() override;
};

#endif