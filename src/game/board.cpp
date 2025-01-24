#include <board.hpp>

/**
 * @brief Constructs a Board object with the specified number of rows and columns.
 * 
 * This constructor initializes a 2D board with the given number of rows and columns.
 * Each cell in the board is dynamically allocated.
 * 
 * @param r The number of rows in the board.
 * @param c The number of columns in the board.
 */
Board::Board(int r, int c) : _rows(r), _cols(c) {
    this->_board.resize(r, std::vector<int>(c, ' '));
}

/**
 * @brief Get the number of columns in the board.
 * 
 * @return ```int``` The number of columns.
 */
int Board::getCols() { 
    return this->_board[0].size(); 
}

/**
 * @brief Get the number of rows in the board.
 * 
 * @return ```int``` The number of rows.
 */
int Board::getRows() { 
    return this->_board.size(); 
}

/**
 * @brief Retrieves the element at the specified row and column in the board.
 * 
 * @param r The row index of the element to retrieve.
 * @param c The column index of the element to retrieve.
 * @return ```int``` The element at the specified row and column.
 */
char Board::getElementAt(int r, int c) { 
    return this->_board[r][c]; 
}

/**
 * @brief Sets the symbol at the specified position on the board.
 * 
 * @param r The row index where the symbol will be placed.
 * @param c The column index where the symbol will be placed.
 * @param symbol The character symbol to be placed on the board.
 */
void Board::setPosition(int r, int c, char symbol) {
    this->_board[r][c] = symbol;
}

/**
 * @brief Checks if the board is completely filled.
 */
bool Board::isBoardFull() {
    for (int i = 0; i < this->_cols; i++) {
        for (int j = 0; j < this->_rows; j++) {
            if (this->_board[i][j] == ' ')
                return false;
        }
    }
    return true;
}

/**
 * @brief Checks if the given row and column indices are within the bounds of the board.
 * 
 * @param r The row index to check.
 * @param c The column index to check.
 */
bool Board::isWithinBounds(int r, int c) {
    return r >= 0 && c >= 0 && r < this->_rows && c < this->_cols;
}   