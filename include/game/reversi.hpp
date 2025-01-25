#ifndef REVERSI_HPP
#define REVERSI_HPP

#include <vector>
#include "game.hpp"

class Reversi: public Game  {

    public:

        struct Direction {
            int dx;
            int dy;

            Direction(int x, int y);
        };
        
        Reversi();

        void readMove() override;

        void validateMove(int row, int col);

        void checkPosition(int row, int col);

        void checkBoundaries(int row, int col); 

        void checkDirections(int row, int col); 

        void checkDirection(int row, int col, char other, const Direction& dir);

        void makeMove() override;

        char isGameFinished() override;

    private:
        std::vector<std::pair<int, int>> toEat;

        static const Direction _dirs[];
};

#endif