#include "exceptions.hpp"
#include "lig4.hpp"

Lig4::Lig4(int rows, int cols): Game(rows, cols) {}

void Lig4::readMove() {
    int col;
    std::cout << "Digite a coluna da jogada: ";
    std::cin >> col;
    try {
        this->validateMove(col);
        this->move.first = col;
    } catch (const InvalidInputException &e) {
        std::cout << e.what() << std::endl;
    }
}

void Lig4::validateMove(int col) {
    if (this->board.getCols() < col || col < 0)
        throw InvalidInputException("Fora dos limites");
    if (this->board.getElementAt(0, col) != ' ')
        throw InvalidInputException("Posicao ocupada");
    
}

void Lig4::makeMove(char symbol) {
    this->readMove();

    for (int i = this->board.getRows() - 1; i >= 0; i--) {
        if (this->board.getElementAt(i, this->move.first) == ' ')
            this->board.setPosition(i, this->move.first, symbol);
            break;
    }
}

int Lig4::isGameFinished() {
    for (int i = 0; i < this->board.getRows(); i++) {
        for (int j = 0; j < this->board.getCols(); i++)
        {
            if (j + 3 < this->board.getCols() && 
            this->board.getElementAt(i, j) == this->board.getElementAt(i, j + 1) &&
            this->board.getElementAt(i, j + 1) == this->board.getElementAt(i, j + 2) &&
            this->board.getElementAt(i, j + 2) == this->board.getElementAt(i, j + 3)
            ) {
                return this->board.getElementAt(i, j);
            }
            if (i + 3 < this->board.getCols() && 
            this->board.getElementAt(i, j) == this->board.getElementAt(i  +1, j) &&
            this->board.getElementAt(i + 1, j) == this->board.getElementAt(i + 2, j) &&
            this->board.getElementAt(i + 2, j) == this->board.getElementAt(i + 3, j)
            ) {
                return this->board.getElementAt(i, j);
            }
            if (j + 3 < this->board.getCols() &&  i + 3 < this->board.getRows() &&
            this->board.getElementAt(i, j) == this->board.getElementAt(i + 1, j + 1) &&
            this->board.getElementAt(i + 1, j + 1) == this->board.getElementAt(i + 2, j + 2) &&
            this->board.getElementAt(i + 2, j + 2) == this->board.getElementAt(i + 3, j + 3)
            ) {
                return this->board.getElementAt(i, j);
            }
            if (j + 3 < this->board.getCols() &&  i - 3 >= 0 &&
            this->board.getElementAt(i, j) == this->board.getElementAt(i - 1, j + 1) &&
            this->board.getElementAt(i - 1, j + 1) == this->board.getElementAt(i - 2, j + 2) &&
            this->board.getElementAt(i - 2, j + 2) == this->board.getElementAt(i - 3, j + 3)
            ) {
                return this->board.getElementAt(i, j);
            }
        }
    }
    if (this->board.isBoardFull())
        return 'D';

    return 'E';
}