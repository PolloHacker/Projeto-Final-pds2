#include "reversi.hpp"
#include "exceptions.hpp"

/**
 * @brief Constructs a Reversi game with an 8x8 board and initializes the starting positions.
 */
Reversi::Reversi(): Game(8, 8) {
    this->board.setPosition(3, 3, 'O');
    this->board.setPosition(3, 4, 'X');
    this->board.setPosition(4, 3, 'X');
    this->board.setPosition(4, 4, 'O');
    
}

Direction::Direction(int x, int y): dx(x), dy(y) {}

/**
 * @brief Array of possible directions for the Reversi game.
 * 
 * This array contains all the possible directions in which a move can be made
 * in the Reversi game. Each direction is represented by a Reversi::Direction
 * object, which takes two parameters indicating the change in row and column
 * respectively.
 * 
 * Directions included:
 * 
 * - (-1, 1): Up-Left
 * 
 * - (0, 1): Up
 * 
 * - (1, 1): Up-Right
 * 
 * - (1, 0): Right
 * 
 * - (1, -1): Down-Right
 * 
 * - (0, -1): Down
 * 
 * - (-1, -1): Down-Left
 * 
 * - (-1, 0): Left
 */
const Direction Reversi::_dirs[] = {
    Direction(-1, 1), 
    Direction(0, 1), 
    Direction(1, 1), 
    Direction(1, 0), 
    Direction(1, -1), 
    Direction(0, -1), 
    Direction(-1, -1), 
    Direction(-1, 0)
};

/**
 * @brief Reads a move from the user and validates it.
 *
 * @throws InvalidInputException if the move is invalid.
 */
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

/**
 * @brief Validates a move in the Reversi game.
 *
 * This function checks if a move is valid by verifying the position,
 * boundaries, and possible directions for flipping opponent's pieces.
 *
 * @param row The row index of the move.
 * @param col The column index of the move.
 */
void Reversi::validateMove(int row, int col) {
    checkPosition(row, col);
    checkBoundaries(row, col);
    checkDirections(row, col);
}

/**
 * @brief Checks if the specified position on the board is occupied.
 *
 * @param row The row index of the position to check.
 * @param col The column index of the position to check.
 * @throws InvalidInputException if the position is occupied.
 */
void Reversi::checkPosition(int row, int col) {
    if (this->board.getElementAt(row, col) != ' ')
        throw InvalidInputException("Posicao ocupada");
}

/**
 * @brief Checks if the given row and column are within the boundaries of the board.
 * 
 * @param row The row index to check.
 * @param col The column index to check.
 * @throws InvalidInputException if the row or column is out of the board's boundaries.
 */
void Reversi::checkBoundaries(int row, int col) {
    if (!this->board.isWithinBounds(row, col))
        throw InvalidInputException("Fora dos limites");
}

/**
 * @brief Checks all possible directions from a given position on the board.
 *
 * This function iterates through all 8 possible directions (up, down, left, right, and the four diagonals)
 * from the specified row and column on the board.
 *
 * @param row The row index of the starting position on the board.
 * @param col The column index of the starting position on the board.
 */
void Reversi::checkDirections(int row, int col) {
    char other = (this->current_player == 'O') ? 'X' : 'O';
    for (int i = 0; i < 8; i++) {
        checkDirection(row, col, other, this->_dirs[i]);
    }
}

/**
 * @brief Checks a specific direction from a given position on the board to find and mark opponent's pieces to be captured.
 *
 * This function checks in the specified direction (given by `dir`) from the position (`row`, `col`) on the board.
 * It looks for a sequence of opponent's pieces (`other`) that are bounded by the current player's piece.
 * If such a sequence is found, the positions of the opponent's pieces are added to the list of pieces to be captured (`toEat`).
 *
 * @param row The starting row position on the board.
 * @param col The starting column position on the board.
 * @param other The character representing the opponent's pieces.
 * @param dir The direction to check, represented by a `Direction` object containing `dx` and `dy`.
 * @throws InvalidInputException if the direction leads to an invalid position or if the sequence is not bounded by the current player's piece.
 */
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

/**
 * @brief Executes a move in the Reversi game.
 * 
 * This function reads the current move, updates the board by setting the positions
 * of the pieces to be captured (flipped) to the current player's piece, and then
 * clears the list of positions to be captured.
 */
void Reversi::makeMove() {
    this->readMove();

    for (const auto& victim: this->toEat) {
        this->board.setPosition(victim.first, victim.second, this->current_player);
    }
    this->toEat.clear();
    this->changePlayer();
}

/**
 * @brief Determines the state of the game and returns the result.
 *
 * @return char 'E' if the game is still ongoing, 'X' if player X has more pieces,
 * 'O' if player O has more pieces, or 'D' if the game is a draw.
 */
char Reversi::isGameFinished() {
    if (hasValidMove()) {
        return 'E';
    }

    int pieces_X = countPieces('X');
    int pieces_O = countPieces('O');

    if (pieces_X > pieces_O) {
        return 'X';
    } else if (pieces_O > pieces_X) {
        return 'O';
    } else {
        return 'D';
    }
}

/**
 * @brief Checks if there is any valid move available for the current player.
 *
 * @return true if there is at least one valid move for either player, false otherwise.
 */
bool Reversi::hasValidMove() {
    if (checkAllMoves()) {
        return true;
    }

    this->changePlayer();
    bool result = checkAllMoves();
    this->changePlayer();

    return result;
}

/**
 * @brief Checks if there are any valid moves available on the Reversi board.
 *
 * @return true if there is at least one valid move available on the board, false otherwise.
 */
bool Reversi::checkAllMoves() {
    for (int i = 0; i < this->board.getRows(); i++) {
        for (int j = 0; j < this->board.getCols(); j++) {
            try {
                this->validateMove(i, j);
                return true;
            } catch (const InvalidInputException& e) {
                continue;
            }
        }
    }
    return false;
}

/**
 * @brief Counts the number of pieces of a specific type on the board.
 * 
 * @param pieceType The type of piece to count (e.g., 'X' or 'O').
 * @return int The total number of pieces of the specified type on the board.
 */
int Reversi::countPieces(char pieceType) {
    int count = 0;
    for (int i = 0; i < this->board.getRows(); i++) {
        for (int j = 0; j < this->board.getCols(); j++) {
            if (this->board.getElementAt(i, j) == pieceType) {
                count++;
            }
        }
    }
    return count;
}