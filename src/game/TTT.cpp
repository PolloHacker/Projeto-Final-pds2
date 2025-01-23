#include "exceptions.hpp"
#include "TTT.hpp"

TTT::TTT(): Game(3, 3) {
    this->board.setCols(3);
    this->board.setRows(3);
}

void TTT::readMove() {
    int row, col;
    std::cout << "Digite a linha e a coluna da jogada: ";
    std::cin >> row >> col;
    try {
        this->validadeMove(row, col);
        this->move[row] = col;
    } catch (const InvalidInputException &e) {
        std::cout << e.what() << std::endl;
    }
    
}

int TTT::checkLine(bool isRow) {
    for (int i = 0; i < 3; i++) {
        char firstElement = isRow ? this->board.getElementAt(i, 0) : this->board.getElementAt(0, i);
        bool isNotEmpty = firstElement != ' ';
        bool isLineEqual = isRow ? (firstElement == this->board.getElementAt(i, 1) && firstElement == this->board.getElementAt(i, 2))
                                 : (firstElement == this->board.getElementAt(1, i) && firstElement == this->board.getElementAt(2, i));
        if (isNotEmpty && isLineEqual) {
            return firstElement;
        }
    }
    return ' ';
}

int TTT::checkRows() {
    return checkLine(true);
}

int TTT::checkColumns() {
    return checkLine(false);
}

int TTT::checkDiagonals() {
    if (this->board.getElementAt(0, 0) == this->board.getElementAt(1, 1) && this->board.getElementAt(1, 1) == this->board.getElementAt(2, 2)) {
        return this->board.getElementAt(0, 0);
    } else if (this->board.getElementAt(0, 2) == this->board.getElementAt(1, 1) && this->board.getElementAt(1, 1) == this->board.getElementAt(2, 0)) {
        return this->board.getElementAt(0, 2);
    }
    return ' ';
}

bool TTT::isDraw() {
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (this->board.getElementAt(i, j) == ' ')
                return false;
        }
    }
    return false;
}

int TTT::isGameFinished() {
    int i, j;

    // Win
    int rowCheck = this->checkRows();
    if (rowCheck != ' ')
        return rowCheck;

    int colCheck = this->checkColumns();
    if (colCheck != ' ')
        return colCheck;

    int diagCheck = this->checkDiagonals();
    if (diagCheck != ' ')
        return diagCheck;

    if (this->isDraw()) 
        return 'D';

    return 'E';
}

void TTT::validadeMove(int row, int col) {
    if (this->board.getElementAt(row, col) != ' ')
        throw InvalidInputException("Posicao ocupada");
    if (!((0 < row < 3) && (0 < col < 3)))
        throw InvalidInputException("Fora dos limites");
}

void TTT::printBoard() {
    for (int i = 0; i < this->board.getRows(); i++) {
        for (int j = 0; j < this->board.getCols(); j++) {
            std::cout << this->board.getElementAt(i, j) << " ";
        }
        std::cout << std::endl;
    }
}
