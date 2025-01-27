#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "lig4.hpp"
#include "exceptions.hpp"

TEST_CASE("Lig4 readMove and validateMove") {
    Lig4 game(6, 7);

    SUBCASE("Valid move") {
        CHECK_NOTHROW(game.validateMove(3));
    }

    SUBCASE("Invalid move - out of bounds") {
        CHECK_THROWS_AS_MESSAGE(game.validateMove(8), InvalidInputException, "[X] - Fora dos limites");
    }

    SUBCASE("Invalid move - position occupied") {
        game.board.setPosition(0, 0, 'X');
        CHECK_THROWS_AS_MESSAGE(game.validateMove(0), InvalidInputException, "[X] - Posicao ocupada");
    }
}

TEST_CASE("Lig4 makeMove") {
    Lig4 game(6, 7);

    SUBCASE("Valid move") {
        std::istringstream input("3\n");
        std::cin.rdbuf(input.rdbuf());
        game.makeMove();
        CHECK(game.board.getElementAt(5, 3) == 'X');
    }

    // SUBCASE("Column full") {
    //     for (int i = 0; i < 6; i++) {
    //         game.board.setPosition(i, 3, 'O');
    //     }
    //     std::istringstream input("3\n");
    //     std::cin.rdbuf(input.rdbuf());
    //     game.makeMove();
    //     CHECK_FALSE(game.board.getElementAt(5, 3) == 'X');
    // }
}

TEST_CASE("Lig4 isGameFinished") {
    Lig4 game(6, 7);

    SUBCASE("Game ongoing") {
        CHECK(game.isGameFinished() == 'E');
    }

    SUBCASE("Horizontal win") {
        for (int i = 0; i < 4; i++) {
            game.board.setPosition(5, i, 'X');
        }
        CHECK(game.isGameFinished() == 'X');
    }

    SUBCASE("Vertical win") {
        for (int i = 0; i < 4; i++) {
            game.board.setPosition(i, 3, 'X');
        }
        CHECK(game.isGameFinished() == 'X');
    }

    SUBCASE("Diagonal win") {
        for (int i = 0; i < 4; i++) {
            game.board.setPosition(i, i, 'X');
        }
        CHECK(game.isGameFinished() == 'X');
    }
}

TEST_CASE("Lig4 checkDirection") {
    Lig4 game(6, 7);

    SUBCASE("Four in a row horizontally") {
        for (int i = 0; i < 4; i++) {
            game.board.setPosition(5, i, 'X');
        }
        CHECK(game.checkDirection(5, 0, 0, 1) == true);
    }

    SUBCASE("Four in a row vertically") {
        for (int i = 0; i < 4; i++) {
            game.board.setPosition(i, 3, 'X');
        }
        CHECK(game.checkDirection(0, 3, 1, 0) == true);
    }

    SUBCASE("Four in a row diagonally (bottom-left to top-right)") {
        for (int i = 0; i < 4; i++) {
            game.board.setPosition(i, i, 'X');
        }
        CHECK(game.checkDirection(0, 0, 1, 1) == true);
    }

    SUBCASE("Four in a row diagonally (top-left to bottom-right)") {
        for (int i = 0; i < 4; i++) {
            game.board.setPosition(3 - i, i, 'X');
        }
        CHECK(game.checkDirection(3, 0, -1, 1) == true);
    }

    SUBCASE("No four in a row") {
        game.board.setPosition(0, 0, 'X');
        game.board.setPosition(1, 1, 'O');
        game.board.setPosition(2, 2, 'X');
        game.board.setPosition(3, 3, 'O');
        CHECK(game.checkDirection(0, 0, 1, 1) == false);
    }
}

TEST_CASE("Lig4 printBoard") {
    Lig4 game(6, 7);

    std::cout << std::endl;
    game.printBoard();
}