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

        void makeMove();

        int isGameFinished() override;

    private:
        std::vector<std::pair<int, int>> toEat;

        static const Direction _dirs[];
};

#endif