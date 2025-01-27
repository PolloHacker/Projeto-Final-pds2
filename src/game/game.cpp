#include "game.hpp"

/**
 * @brief Constructs a new Game object with the specified number of rows and columns.
 * 
 * @param rows The number of rows for the game board.
 * @param cols The number of columns for the game board.
 */
Game::Game(int rows, int cols): board(rows, cols) {
    this->current_player = 'X';
}

void Game::changePlayer() {
    this->current_player = (this->current_player == 'X') ? 'O' : 'X';
}

/**
 * @brief Prints the current state of the game board to the standard output.
 */
void Game::printBoard() {
    //flushTerminalInGame();
    std::cout << "  ";
    for (int j = 0; j < this->board.getCols(); j++) {
        std::cout << j << " ";
    }
    std::cout << std::endl;

    for (int i = 0; i < this->board.getRows(); i++) {
        std::cout << i << " ";
        for (int j = 0; j < this->board.getCols(); j++) {
            if (this->board.getElementAt(i, j) == ' ')
                std::cout << ". ";
            else
                std::cout << this->board.getElementAt(i, j) << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "+---------------------------+" << std::endl;
}