#include "reversi.hpp"
#include "exceptions.hpp"

Reversi::Reversi(): Game(8, 8) {
    this->board.setPosition(3, 3, 'O');
    this->board.setPosition(3, 4, 'X');
    this->board.setPosition(4, 3, 'X');
    this->board.setPosition(4, 4, 'O');
    
}

Reversi::Direction::Direction(int x, int y): dx(x), dy(y) {}

static const Reversi::Direction _dirs[] = {
    Reversi::Direction(-1, 1), 
    Reversi::Direction(0, 1), 
    Reversi::Direction(1, 1), 
    Reversi::Direction(1, 0), 
    Reversi::Direction(1, -1), 
    Reversi::Direction(0, -1), 
    Reversi::Direction(-1, -1), 
    Reversi::Direction(-1, 0)
};

void Reversi::readMove() {
    int row, col;
    std::cout << "Digite a linha e a coluna da jogada: ";
    std::cin >> row >> col;
    try {
        this->validateMove(row, col);
        this->move.first = row;
        this->move.second = col;
    } catch (const InvalidInputException &e) {
        std::cout << e.what() << std::endl;
    }
}

void Reversi::validateMove(int row, int col) {
    checkPosition(row, col);
    checkBoundaries(row, col);
    checkDirections(row, col);
}

void Reversi::checkPosition(int row, int col) {
    if (this->board.getElementAt(row, col) != ' ')
        throw InvalidInputException("Posicao ocupada");
}

void Reversi::checkBoundaries(int row, int col) {
    if (!this->board.isWithinBounds(row, col))
        throw InvalidInputException("Fora dos limites");
}

void Reversi::checkDirections(int row, int col) {
    char other = this->current_player == 'O' ? 'X' : 'O';
    for (int i = 0; i < 8; i++) {
        checkDirection(row, col, other, this->_dirs[i]);
    }
}

void Reversi::checkDirection(int row, int col, char other, const Direction& dir) {
    std::vector<std::pair<int, int>> toEatAux;

    int x = row + dir.dx;
    int y = col + dir.dy;

    bool hasFoundOther = false;

    while (this->board.isWithinBounds(x, y) && this->board.getElementAt(x, y) == other) {
        hasFoundOther = true;
        toEatAux.emplace_back(x, y);
        x += dir.dx;
        y += dir.dy;
    }
    if (hasFoundOther && this->board.isWithinBounds(x, y)) {
        if (this->board.getElementAt(x, y) != this->current_player)
            throw InvalidInputException("Posicao invalida");
        else if (this->board.getElementAt(x, y) == this->current_player) {
            this->toEat.insert(this->toEat.begin(), toEatAux.begin(), toEatAux.end());
        }
    }
}

void Reversi::makeMove() {
    this->readMove();

    for (const auto& victim: this->toEat) {
        this->board.setPosition(victim.first, victim.second, this->current_player);
    }
    this->toEat.clear();
}