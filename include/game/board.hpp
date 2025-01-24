#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <memory>

class Board {
    private:
        int _rows;
        int _cols;
        std::unique_ptr<std::unique_ptr<int[]>[]> _board;

    public:

        Board(int r, int c);

        int getCols();
        int getRows();

        int getElementAt(int r, int c);

        void setCols(int c);

        void setRows(int r);

        void setPosition(int r, int c, char symbol);

        bool isBoardFull();

        bool isWithinBounds(int r, int c);
};

#endif