#include "reversi.hpp"

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
 * - (-1, 1): Down-Left
 * 
 * - (0, 1): Down
 * 
 * - (1, 1): Down-Right
 * 
 * - (1, 0): Right
 * 
 * - (1, -1): Up-Right
 * 
 * - (0, -1): Up
 * 
 * - (-1, -1): Up-Left
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
 * @brief Checks if the specified position on the board is occupied.
 *
 * @param row The row index of the position to check.
 * @param col The column index of the position to check.
 * @throws InvalidInputException if the position is occupied.
 */
void Reversi::checkPosition(int row, int col) {
    if (this->board.getElementAt(row, col) != ' ')
        throw InvalidInputException("[X] - Posicao ocupada");
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
        throw InvalidInputException("[X] - Fora dos limites");
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
 * @returns true if the direction is valid and contains opponent's pieces to be captured, false otherwise.
 */
bool Reversi::checkDirection(const int row, const int col, char other, const Direction& dir) {
    int x = row + dir.dx;
    int y = col + dir.dy;

    bool hasFoundOther = false;

    while (this->board.isWithinBounds(x, y) && this->board.getElementAt(x, y) == other) {
        hasFoundOther = true;
        x += dir.dx;
        y += dir.dy;
    }
    if (hasFoundOther && this->board.isWithinBounds(x, y)) {
        if (this->board.getElementAt(x, y) == this->current_player) {
            return true;
        }
    }
    return false;
}

// void Reversi::addPositionsToEat(const int row, const int col, const Direction& dir) {
//     char other = (this->current_player == 'O') ? 'X' : 'O';
//     int x = row + dir.dx;
//     int y = col + dir.dy;

//     while (this->board.isWithinBounds(x, y) && this->board.getElementAt(x, y) == other) {
//         //std::cout << "Adicionando posicao para comer: " << row << " " << col << std::endl;
//         this->toEat.emplace_back(x, y);
//         x += dir.dx;
//         y += dir.dy;
//     }
// }

/**
 * @brief Checks all possible directions from a given position on the board.
 *
 * This function iterates through all 8 possible directions (up, down, left, right, and the four diagonals)
 * from the specified row and column on the board.
 *
 * @param row The row index of the starting position on the board.
 * @param col The column index of the starting position on the board.
 */
void Reversi::checkDirections(const int row, const int col) {
    char other = (this->current_player == 'O') ? 'X' : 'O';
    bool isValid = false;

    for (int i = 0; i < 8; i++) {
        if (this->checkDirection(row, col, other, this->_dirs[i])) {
            isValid = true;
        }
    }
    if (!isValid) {
        throw InvalidInputException("[X] - Jogada invalida");
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
void Reversi::validateMove(const int row, const int col) {
    checkBoundaries(row, col);
    checkPosition(row, col);
    checkDirections(row, col);
}

/**
 * @brief Reads a move from the user and validates it.
 *
 * @throws InvalidInputException if the move is invalid.
 */
void Reversi::readMove() {
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
 * @brief Executes a move in the Reversi game.
 * 
 * This function performs the following steps:
 * 1. Determines the opponent's piece based on the current player.
 * 2. Reads the move from the player.
 * 3. Sets the player's piece on the board at the specified move position.
 * 4. Checks all 8 possible directions from the move position to find and flip the opponent's pieces.
 * 5. Flips the opponent's pieces to the current player's pieces if they are bounded by the current player's pieces.
 * 6. Changes the current player to the opponent.
 */
void Reversi::makeMove() {
    char other = (this->current_player == 'O') ? 'X' : 'O';

    this->readMove();
    this->board.setPosition(this->move.first, this->move.second, this->current_player);

    for (int i = 0; i < 8; ++i) {
        int x = this->move.first + this->_dirs[i].dx;
        int y = this->move.second + this->_dirs[i].dy;
        std::vector<std::pair<int, int>> toEat;
        while (x >= 0 && x < this->board.getCols() && y >= 0 && y < this->board.getRows() && this->board.getElementAt(x, y) == other) {
            toEat.emplace_back(x, y);
            x += this->_dirs[i].dx;
            y += this->_dirs[i].dy;
        }
        if (x >= 0 && x < this->board.getCols() && y >= 0 && y < this->board.getRows() && this->board.getElementAt(x, y) == this->current_player) {
            for (const auto& p : toEat) {
                this->board.setPosition(p.first, p.second, this->current_player);
            }
        }
    }
    this->changePlayer();
}


/**
 * @brief Checks if the game of Reversi is finished.
 * 
 * This function determines if the game has ended by checking for valid moves
 * for the current player. If no valid moves are found, it switches to the 
 * other player and checks again. If neither player has valid moves, the game 
 * is considered finished. The function then counts the pieces for each player 
 * on the board and returns the result.
 * 
 * @return 'E' if the game is not finished and there are valid moves.
 *         'X' if player 'X' has more pieces and wins.
 *         'O' if player 'O' has more pieces and wins.
 *         'D' if the game is a draw (both players have the same number of pieces).
 */
char Reversi::isGameFinished(){
   bool hasValidMove = false;

   for (int i = 0; i < this->board.getRows(); i++) {
       for (int j = 0; j < this->board.getCols(); j++) {
            try {
                this->validateMove(i, j);
                hasValidMove = true;           
            } catch (const InvalidInputException &e) {
                continue;
            }
        }
    }

    if (!hasValidMove) {
        char other = (this->current_player == 'O') ? 'X' : 'O';
        this->current_player = other;
        for (int i = 0; i < this->board.getRows(); i++) {
            for (int j = 0; j < this->board.getCols(); j++) {
                try {
                    this->validateMove(i, j);
                    hasValidMove = true;           
                } catch (const InvalidInputException &e) {
                    continue;
                }
            }
        }
        this->current_player = (this->current_player == 'O') ? 'X' : 'O';
    }

    if (hasValidMove) {
        return 'E';
    }


    int pieces_X = 0;
    int pieces_O = 0;
    for (int i = 0; i < this->board.getRows(); i++) {
        for (int j = 0; j < this->board.getCols(); j++) {
            char piece = this->board.getElementAt(i, j);
            if (piece == 'X') {
                pieces_X++;
            } else if (piece == 'O') {
                pieces_O++;
            }
        }
    }

    if (pieces_X > pieces_O) {
        return 'X'; 
    } else if (pieces_O > pieces_X) {
        return 'O'; 
    } else {
        return 'D'; 
    }
}
