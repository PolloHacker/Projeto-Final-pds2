#ifndef BOARD_HPP
#define BOARD_HPP
#define private public

#include <iostream>
#include <vector>
#include <memory>

class Board {
    private:
        int _rows;
        int _cols;
        std::vector<std::vector<int>> _board;

    public:

        Board(int r, int c);

        int getCols();
        int getRows();

        char getElementAt(int r, int c);

        void setPosition(int r, int c, char symbol);

        bool isBoardFull();

        bool isWithinBounds(int r, int c);
};

#endif