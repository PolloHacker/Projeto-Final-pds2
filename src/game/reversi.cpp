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
    int i;

    if (this->board.getElementAt(row, col) != ' ')
        throw InvalidInputException("Posicao ocupada");
    else if (row < 0 || col < 0 || row >= this->board.getRows() || col >= this->board.getCols())
        throw InvalidInputException("Fora dos limites");

    char other = this->current_player == 'O' ? 'X' : 'O';
    for (i = 0; i < 8; i++) {
        int x = row + this->_dirs[i].dx;
        int y = col + this->_dirs[i].dy;
        bool hasFoundOther = false;
        std::vector<std::pair<int, int>> toEatAux;
        while (x >= 0 && y >= 0 && x < this->board.getRows() && y < this->board.getCols() && this->board.getElementAt(x, y) == other) {
            hasFoundOther = true;
            toEatAux.emplace_back(x, y);
            x += this->_dirs[i].dx;
            y += this->_dirs[i].dy;
        }
        if (hasFoundOther && x >= 0 && y >= 0 && x < this->board.getRows() && y < this->board.getCols()) {
            if (this->board.getElementAt(x, y) != this->current_player)
                throw InvalidInputException("Posicao invalida");
            else if (this->board.getElementAt(x, y) == this->current_player) {
                this->toEat.insert(this->toEat.begin(), toEatAux.begin(), toEatAux.end());
            }
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