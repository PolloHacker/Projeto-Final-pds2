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

bool TTT::isGameFinished() {
    int i, j;

    // Win
    for (i = 0; i < 3; i++) {
        // Linha
        if (this->board.getElementAt(i, 0) != ' ' && this->board.getElementAt(i, 0) == this->board.getElementAt(i, 1) == this->board.getElementAt(i, 2)) {
            return this->board.getElementAt(i, 0);
        }
        // Coluna
        else if (this->board.getElementAt(0, i) != ' ' && this->board.getElementAt(0, i) == this->board.getElementAt(1, i) == this->board.getElementAt(2, i)) {
            return this->board.getElementAt(i, 0);
        }
    }

    // Diagonais
    if (this->board.getElementAt(0, 0) == this->board.getElementAt(1, 1) == this->board.getElementAt(2, 2)) {
        return this->board.getElementAt(0, 0);
    } else if (this->board.getElementAt(0, 2) == this->board.getElementAt(1, 1) == this->board.getElementAt(2, 0)) {
        return this->board.getElementAt(0, 2);
    }

    // Empate
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (this->board.getElementAt(i, j) == ' ')
                return 'A';
        }
    }
    return 'E';
}

void TTT::validadeMove(int row, int col) {
    // TODO implement move validation
    if (this->board.getElementAt(row, col) != ' ')
        throw InvalidInputException("Posicao ocupada");
    if (row > 3 || col > 3 || row < 0 || col < 0)
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
