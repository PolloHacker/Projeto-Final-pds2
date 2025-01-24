#include <board.hpp>

Board::Board(int r, int c) : _rows(r), _cols(c) {
    this->_board = std::make_unique<std::unique_ptr<int[]>[]>(r);
    for (int i = 0; i < r; i++) {
        this->_board[i] = std::make_unique<int[]>(c);
    }
}

int Board::getCols() { 
    return this->_cols; 
}

int Board::getRows() { 
    return this->_rows; 
}

int Board::getElementAt(int r, int c) { 
    return this->_board[r][c]; 
}

void Board::setCols(int c) { 
    if (c <= 0) {
        std::cout << "Erro: Tamanho inválido" << std::endl;
        return;
    }
    this->_cols = c;
}

void Board::setRows(int r) { 
    if (r <= 0) {
        std::cout << "Erro: Tamanho inválido" << std::endl;
        return;
    }
    this->_rows = r;
}

void Board::setPosition(int r, int c, char symbol) {
    this->_board[r][c] = symbol;
}

bool Board::isBoardFull() {
    for (int i = 0; i < this->_cols; i++) {
        for (int j = 0; j < this->_rows; j++) {
            if (this->_board[i][j] == ' ')
                return false;
        }
    }
    return true;
}

bool Board::isWithinBounds(int r, int c) {
    return r >= 0 && c >= 0 && r < this->_rows && c < this->_cols;
}   