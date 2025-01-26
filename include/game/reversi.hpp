#ifndef REVERSI_HPP
#define REVERSI_HPP
#define private public

#include <vector>
#include "game.hpp"
#include "string_utils.hpp"

struct Direction {
    int dx;
    int dy;

    Direction(int x, int y);
};

class Reversi: public Game  {
    private:
        
        std::vector<std::pair<int, int>> toEat;

        static const Direction _dirs[];

        void readMove() override;

        void validateMove(int row, int col);

        void checkPosition(int row, int col);

        void checkBoundaries(int row, int col); 

        void checkDirections(int row, int col); 

        void checkDirection(int row, int col, char other, const Direction& dir);

        bool hasValidMove();

        bool checkAllMoves();

        int countPieces(char player);

    public:
        
        Reversi();

        void makeMove() override;

        char isGameFinished() override;
};

#endif