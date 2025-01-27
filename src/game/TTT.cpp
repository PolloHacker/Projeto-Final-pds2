#include "TTT.hpp"

/**
 * @brief Constructs a TTT (Tic-Tac-Toe) game object.
 */
TTT::TTT(): Game(3, 3) {}

/**
 * @brief Reads a move from the user and validates it.
 * 
 * @throws InvalidInputException if the move is invalid.
 */
void TTT::readMove() {
    std::string a1, a2;
    std::pair<int,int> move;

    std::cout << "Vez do jogador " << this->current_player << std::endl;
    std::cout << "Digite a linha e a coluna da jogada: ";
    std::cin >> a1 >> a2;
    try {
        move = StringUtils::IsValidMoveInput(a1, a2);
        this->validateMove(move.first, move.second);

        this->move.first = move.first;
        this->move.second = move.second;
    } catch (const InvalidInputException &e) {
        std::cout << e.what() << std::endl;
        this->readMove();
    }
    
}

/**
 * @brief Validates a move in the Tic-Tac-Toe game.
 * 
 * This function checks if the move specified by the row and column
 * is valid. A move is considered valid if the specified position
 * on the board is empty and within the bounds of the board.
 * 
 * @param row The row index of the move.
 * @param col The column index of the move.
 * 
 * @throws InvalidInputException if the position is already occupied
 *         or if the position is out of the board's bounds.
 */
void TTT::validateMove(int row, int col) {
    bool isRowValid = (0 <= row && row < 3);
    bool isColValid = (0 <= col && col < 3);
    if (!(isRowValid && isColValid))
        throw InvalidInputException("[X] - Fora dos limites");
    if (this->board.getElementAt(row, col) != ' ')
        throw InvalidInputException("[X] - Posicao ocupada");
}

/**
 * @brief Makes a move in the Tic-Tac-Toe game.
 * 
 * This function reads the player's move and sets the specified symbol
 * at the corresponding position on the game board.
 * 
 */
void TTT::makeMove() {
    this->readMove();

    this->board.setPosition(this->move.first, this->move.second, this->current_player);
    this->changePlayer();
}

/**
 * @brief Checks if there is a winning line (row or column) in the Tic-Tac-Toe board.
 *
 * This function iterates through each row or column of the board (depending on the isRow parameter)
 * and checks if all elements in the row or column are the same and not empty.
 *
 * @param isRow A boolean indicating whether to check rows (true) or columns (false).
 * @return The character representing the winner ('X' or 'O') if a winning line is found, 
 *         or a space character (' ') if no winning line is found.
 */
int TTT::checkLine(bool isRow) {
    for (int i = 0; i < 3; i++) {
        char firstElement = isRow ? this->board.getElementAt(i, 0) : this->board.getElementAt(0, i);
        bool isNotEmpty = firstElement != ' ';
        bool isLineEqual = isRow ? (firstElement == this->board.getElementAt(i, 1) && firstElement == this->board.getElementAt(i, 2))
                                 : (firstElement == this->board.getElementAt(1, i) && firstElement == this->board.getElementAt(2, i));
        if (isNotEmpty && isLineEqual) {
            return firstElement;
        }
    }
    return ' ';
}

/**
 * @brief Checks the rows in the Tic-Tac-Toe game for a win condition.
 * 
 * @return int The result of the checkLine method, indicating the status of the rows.
 */
int TTT::checkRows() {
    return checkLine(true);
}

/**
 * @brief Checks the columns in the game.
 * 
 * @return int Returns an integer indicating the result of the column check.
 */
int TTT::checkColumns() {
    return checkLine(false);
}

/**
 * @brief Checks the diagonals of the Tic-Tac-Toe board to determine if there is a winner.
 *
 * This function checks both the main diagonal (from top-left to bottom-right) and the anti-diagonal
 * (from top-right to bottom-left) of the board. If all three elements in either diagonal are the same,
 * it returns the value of that element (which represents the winner). If neither diagonal has a winner,
 * it returns a space character (' ').
 *
 * @return The value of the winning element ('X' or 'O') if there is a winner, otherwise returns ' '.
 */
int TTT::checkDiagonals() {
    if (this->board.getElementAt(0, 0) == this->board.getElementAt(1, 1) && this->board.getElementAt(1, 1) == this->board.getElementAt(2, 2)) {
        return this->board.getElementAt(0, 0);
    } else if (this->board.getElementAt(0, 2) == this->board.getElementAt(1, 1) && this->board.getElementAt(1, 1) == this->board.getElementAt(2, 0)) {
        return this->board.getElementAt(0, 2);
    }
    return ' ';
}

/**
 * @brief Checks the current state of the game to determine if it has finished.
 *
 * @return int - The result of the game:
 * 
 * - Winning player's symbol if there is a winner.
 * 
 * - 'D' if the game is a draw.
 * 
 * - 'E' if the game is still ongoing.
 */
char TTT::isGameFinished() {
    // Win
    int rowCheck = this->checkRows();
    if (rowCheck != ' ')
        return rowCheck;

    int colCheck = this->checkColumns();
    if (colCheck != ' ')
        return colCheck;

    int diagCheck = this->checkDiagonals();
    if (diagCheck != ' ')
        return diagCheck;

    if (this->board.isBoardFull()) 
        return 'D';

    return 'E';
}
