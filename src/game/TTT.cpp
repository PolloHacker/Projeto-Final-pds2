#include "TTT.hpp"


TTT::TTT(int rows = 3, int cols = 3) : Game(rows, cols) {
    this->board.setCols(cols);
    this->board.setRows(rows);
}

void TTT::readMove() {
    int row, col;
    std::cout << "Digite a linha e a coluna da jogada: ";
    std::cin >> row >> col;
    this->move[row] = col;
}

bool TTT::isGameFinished() {
    // TODO implement game finish condition
}

void TTT::validadeMove() {
    // TODO implement move validation
}

void TTT::printBoard() {
    for (int i = 0; i < this->board.getRows(); i++) {
        for (int j = 0; j < this->board.getCols(); j++) {
            std::cout << this->board.getElementAt(i, j) << " ";
        }
        std::cout << std::endl;
    }
}

TTT::~TTT() {
    // TODO implement destructor
}