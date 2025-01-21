#ifndef GAME_HPP
#define GAME_HPP

#include <map>
#include "board.hpp"


class Game {
    protected:
        Board board;
        std::pair<int, int> move;

    public:

        Game(int rows, int cols) : board(rows, cols) {}

        virtual void readMove() = 0;

        virtual int isGameFinished() = 0;

        virtual void validadeMove() = 0;

        virtual void printBoard() = 0;

        virtual ~Game() = default;
};

#endif