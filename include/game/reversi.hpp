#ifndef REVERSI_HPP
#define REVERSI_HPP

#include <vector>

#include "game.hpp"
#include "string_utils.hpp"
#include "exceptions.hpp"

struct Direction {
    int dx;
    int dy;

    Direction(int x, int y);
};

class Reversi: public Game  {
    private:
        
        // std::vector<std::pair<int, int>> toEat;

        static const Direction _dirs[];

        void readMove() override;

        void validateMove(const int row, const int col);

        void checkPosition(const int row, const int col);

        void checkBoundaries(const int row, const int col); 

        void checkDirections(const int row, const int col); 

        bool checkDirection(const int row, const int col, char other, const Direction& dir);

        void addPositionsToEat(int row, int col, const Direction& dir);

    public:
        
        Reversi();

        void makeMove() override;

        char isGameFinished() override;
};

#endif