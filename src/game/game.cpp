#include "game.hpp"

Game::Game(int rows, int cols): board(rows, cols) {}

void Game::printBoard() {
    for (int i = 0; i < this->board.getRows(); i++) {
        for (int j = 0; j < this->board.getCols(); j++) {
            std::cout << this->board.getElementAt(i, j) << " ";
        }
        std::cout << std::endl;
    }
}