#ifndef GAME_HPP
#define GAME_HPP

#include <map>
#include "board.hpp"


class Game {
    protected:
        Board board;
        std::pair<int, int> move;
        char current_player;

    public:

        Game(int rows, int cols);

        virtual void readMove() = 0;

        virtual void makeMove() = 0;

        virtual char isGameFinished() = 0;

        void changePlayer();

        virtual void printBoard();

        virtual ~Game() = default;
};

#endif