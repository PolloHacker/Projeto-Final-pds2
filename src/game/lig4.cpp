#include "exceptions.hpp"
#include "lig4.hpp"

/**
 * @brief Constructs a new Lig4 object with the specified number of rows and columns.
 * 
 * @param rows The number of rows for the Lig4 game board.
 * @param cols The number of columns for the Lig4 game board.
 */
Lig4::Lig4(int rows, int cols): Game(rows, cols) {}

/**
 * @brief Reads a move from the user and validates it.
 * 
 * @throws InvalidInputException if the input column is invalid.
 */
void Lig4::readMove() {
    std::string in;
    int col;

    std::cout << "Digite a coluna da jogada: ";
    std::cin >> in;
    try {
        col = StringUtils::IsValidMoveInput(in);
        std::cout << col << std::endl;
        this->validateMove(col);
        this->move.first = col;
    } catch (const InvalidInputException &e) {
        std::cout << e.what() << std::endl;
        this->readMove();
    }
}

/**
 * @brief Validates a move in the Lig4 game.
 * 
 * This function checks if the specified column is within the valid range and if the top position
 * of the column is not already occupied.
 * 
 * @param col The column number to validate.
 * @throws InvalidInputException if the column is out of bounds or the position is occupied.
 */
void Lig4::validateMove(int col) {
    if (!(0 <= col && col < this->board.getCols()))
        throw InvalidInputException("Fora dos limites");
    if (this->board.getElementAt(0, col) != ' ')
        throw InvalidInputException("Posicao ocupada");
    
}

/**
 * @brief Executes a move in the Lig4 game.
 * 
 * This function reads the player's move and updates the game board.
 * It places the current player's piece in the lowest available position in the
 * specified column.
 * 
 * @note Assumes that the move is valid and within the bounds of the board.
 */
void Lig4::makeMove() {
    this->readMove();

    for (int i = this->board.getRows() - 1; i >= 0; i--) {
        if (this->board.getElementAt(i, this->move.first) == ' ')
            this->board.setPosition(i, this->move.first, this->current_player);
            this->changePlayer();
            break;
    }
}

/**
 * @brief Checks if the game is finished.
 * 
 * This function iterates through the entire game board and checks for a winning condition
 * in four possible directions: horizontal, vertical and diagonals. If a winning condition is found, it returns the
 * element (player) that has won. If the board is full and no winning condition is found, 
 * it returns 'D' indicating a draw. If the game is still ongoing, it returns 'E'.
 * 
 * @return ```int``` The element (player) that has won, ```'D'``` for draw, or ```'E'``` for ongoing game.
 */
char Lig4::isGameFinished() {
    for (int i = 0; i < this->board.getRows(); i++) {
        for (int j = 0; j < this->board.getCols(); j++) {
            if (checkDirection(i, j, 0, 1) || checkDirection(i, j, 1, 0) || 
                checkDirection(i, j, 1, 1) || checkDirection(i, j, -1, 1)) {
                return this->board.getElementAt(i, j);
            }
        }
    }
    if (this->board.isBoardFull())
        return 'D';

    return 'E';
}

/**
 * @brief Checks if there are four consecutive elements in a specified direction.
 *
 * This function checks if there are four consecutive elements starting from the 
 * given position (row, col) in the direction specified by (rowDir, colDir).
 *
 * @param row The starting row position.
 * @param col The starting column position.
 * @param rowDir The row direction to check (e.g., 1 for down, -1 for up, 0 for no vertical movement).
 * @param colDir The column direction to check (e.g., 1 for right, -1 for left, 0 for no horizontal movement).
 */
bool Lig4::checkDirection(int row, int col, int rowDir, int colDir) {
    bool rowOutOfBounds = (row + 3 * rowDir >= this->board.getRows() || row + 3 * rowDir < 0);
    bool colOutOfBounds = (col + 3 * colDir >= this->board.getCols() || col + 3 * colDir < 0);
    
    if (rowOutOfBounds || colOutOfBounds) {
        return false;
    }
    char first = this->board.getElementAt(row, col);
    if (first == ' ') return false;
    for (int k = 1; k <= 3; k++) {
        if (this->board.getElementAt(row + k * rowDir, col + k * colDir) != first) {
            return false;
        }
    }
    return true;
}


/**
 * @brief Prints the current state of the game board to the standard output.
 */
void Lig4::printBoard() {
    for (int j = 0; j < this->board.getCols(); j++) {
        std::cout << j << " ";
    }
    std::cout << std::endl;

    for (int i = 0; i < this->board.getRows(); i++) {
        for (int j = 0; j < this->board.getCols(); j++) {
            if (this->board.getElementAt(i, j) == ' ')
                std::cout << ". ";
            else
                std::cout << this->board.getElementAt(i, j) << " ";
        }
        std::cout << std::endl;
    }
}