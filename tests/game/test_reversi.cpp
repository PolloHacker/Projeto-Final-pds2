#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "reversi.hpp"
#include "exceptions.hpp"

TEST_CASE("Test initial board setup") {
    Reversi game;
    CHECK(game.board.getElementAt(3, 3) == 'O');
    CHECK(game.board.getElementAt(3, 4) == 'X');
    CHECK(game.board.getElementAt(4, 3) == 'X');
    CHECK(game.board.getElementAt(4, 4) == 'O');
}

TEST_CASE("Test valid move") {
    Reversi game;
    CHECK_NOTHROW(game.validateMove(2, 3));
}

TEST_CASE("Test invalid move - position occupied") {
    Reversi game;
    CHECK_THROWS_AS(game.validateMove(3, 3), InvalidInputException);
}

TEST_CASE("Test invalid move - out of bounds") {
    Reversi game;
    CHECK_THROWS_AS(game.validateMove(8, 8), InvalidInputException);
}

TEST_CASE("Test direction checking") {
    Reversi game;
    game.board.setPosition(2, 3, 'X');
    game.board.setPosition(3, 3, 'O');
    game.board.setPosition(4, 3, 'X');
    CHECK_NOTHROW(game.checkDirection(2, 3, 'O', Direction(1, 0)));
}

TEST_CASE("Test make move") {

    SUBCASE("valid input") {
        Reversi game;
        std::istringstream input("2 3\n");
        std::cin.rdbuf(input.rdbuf());
        CHECK_NOTHROW(game.makeMove());
    }

    SUBCASE("invalid input, retry") {
        Reversi game;
        std::istringstream input("FELIPE MATEUS\n2 3\n");
        std::cin.rdbuf(input.rdbuf());
        game.makeMove();
        CHECK(game.move.first == 2);
        CHECK(game.move.second == 3);
    }
}

TEST_CASE("Test game finished - ongoing") {
    Reversi game;
    CHECK(game.isGameFinished() == 'E');

    SUBCASE("still ongoing") {
        Reversi game;
        game.board.setPosition(0, 0, 'O');
        game.board.setPosition(0, 1, 'O');
        game.board.setPosition(0, 2, 'O');
        CHECK(game.isGameFinished() == 'E');
    }

    SUBCASE("Test game finished - draw") {
        Reversi game;
        game.board.setPosition(0, 0, 'X');
        game.board.setPosition(0, 1, 'O');
        game.board.setPosition(0, 2, 'X');
        game.board.setPosition(0, 3, 'O');
        CHECK(game.isGameFinished() == 'E');
    }
}

TEST_CASE("Test game finished - player X wins") {
    Reversi game;

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            game.board.setPosition(i, j, 'X');
        }
    }
    CHECK(game.isGameFinished() == 'X');
}

TEST_CASE("Test game finished - player O wins") {
    Reversi game;
    
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            game.board.setPosition(i, j, 'O');
        }
    }
    CHECK(game.isGameFinished() == 'O');
}

TEST_CASE("Test game finished - draw") {
    Reversi game;

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if ((i + j) % 2 == 0) {
                game.board.setPosition(i, j, 'X');
            } else {
                game.board.setPosition(i, j, 'O');
            }
        }
    }
    CHECK(game.isGameFinished() == 'D');
}

TEST_CASE("Test print board") {
    Reversi game;
    std::ostringstream output;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf(output.rdbuf());

    game.printBoard();

    std::cout.rdbuf(oldCoutBuffer);
    std::string expectedOutput =
        "  0 1 2 3 4 5 6 7\n"
        "0 . . . . . . . .\n"
        "1 . . . . . . . .\n"
        "2 . . . . . . . .\n"
        "3 . . . O X . . .\n"
        "4 . . . X O . . .\n"
        "5 . . . . . . . .\n"
        "6 . . . . . . . .\n"
        "7 . . . . . . . .\n";

    CHECK(output.str() == expectedOutput);
}