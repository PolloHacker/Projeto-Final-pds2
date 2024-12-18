#ifndef GAME_HPP
#define GAME_HPP

#include <map>
#include <board.hpp>


class Game {
    private:
        Board board;
        std::map<int, int> move;

    public:

        Game(int rows, int cols): board(rows, cols) {}

        void readMove();

        bool isGameFinished();

        void validadeMove();

        void printBoard();
};

#endif