#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>

class Board {
    private:
        int _rows;
        int _cols;
        int **_board;

    public:

        Board(int r, int c): _rows(r), _cols(c), _board(nullptr) {}

        int getCols();
        int getRows();

        void setCols(int c);

        void setRows(int r);
};

#endif