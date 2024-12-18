#include <board.hpp>


int Board::getCols() { return this->_cols; }

int Board::getRows() { return this->_rows; }

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