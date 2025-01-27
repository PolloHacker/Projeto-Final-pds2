#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "TTT.hpp"
#include "exceptions.hpp"

TEST_CASE("TTT::validateMove") {
    TTT game;

    SUBCASE("Valid move") {
        CHECK_NOTHROW(game.validateMove(0, 0));
    }

    SUBCASE("Move out of bounds") {
        CHECK_THROWS_AS_MESSAGE(game.validateMove(-1, 0), InvalidInputException, "[X] - Fora dos limites");
        CHECK_THROWS_AS_MESSAGE(game.validateMove(0, -1), InvalidInputException, "[X] - Fora dos limites");
        CHECK_THROWS_AS_MESSAGE(game.validateMove(3, 0), InvalidInputException, "[X] - Fora dos limites");
        CHECK_THROWS_AS_MESSAGE(game.validateMove(0, 3), InvalidInputException, "[X] - Fora dos limites");
    }

    SUBCASE("Move to occupied position") {
        game.board.setPosition(0, 0, 'X');
        CHECK_THROWS_AS_MESSAGE(game.validateMove(0, 0), InvalidInputException, "[X] - Posicao ocupada");
    }
}

TEST_CASE("TTT::checkLine") {
    TTT game;

    SUBCASE("Check rows for a win") {
        game.board.setPosition(0, 0, 'X');
        game.board.setPosition(0, 1, 'X');
        game.board.setPosition(0, 2, 'X');
        CHECK(game.checkRows() == 'X');
    }

    SUBCASE("Check columns for a win") {
        game.board.setPosition(0, 0, 'O');
        game.board.setPosition(1, 0, 'O');
        game.board.setPosition(2, 0, 'O');
        CHECK(game.checkColumns() == 'O');
    }

    SUBCASE("No winning line") {
        CHECK(game.checkRows() == ' ');
        CHECK(game.checkColumns() == ' ');
    }
}

TEST_CASE("TTT::checkDiagonals") {
    TTT game;

    SUBCASE("Check main diagonal for a win") {
        game.board.setPosition(0, 0, 'X');
        game.board.setPosition(1, 1, 'X');
        game.board.setPosition(2, 2, 'X');
        CHECK(game.checkDiagonals() == 'X');
    }

    SUBCASE("Check anti-diagonal for a win") {
        game.board.setPosition(0, 2, 'O');
        game.board.setPosition(1, 1, 'O');
        game.board.setPosition(2, 0, 'O');
        CHECK(game.checkDiagonals() == 'O');
    }

    SUBCASE("No winning diagonal") {
        CHECK(game.checkDiagonals() == ' ');
    }
}

TEST_CASE("TTT::isGameFinished") {
    TTT game;

    SUBCASE("Game ongoing") {
        CHECK(game.isGameFinished() == 'E');
    }

    SUBCASE("Game won by row") {
        game.board.setPosition(0, 0, 'X');
        game.board.setPosition(0, 1, 'X');
        game.board.setPosition(0, 2, 'X');
        CHECK(game.isGameFinished() == 'X');
    }

    SUBCASE("Game won by column") {
        game.board.setPosition(0, 0, 'O');
        game.board.setPosition(1, 0, 'O');
        game.board.setPosition(2, 0, 'O');
        CHECK(game.isGameFinished() == 'O');
    }

    SUBCASE("Game won by diagonal") {
        game.board.setPosition(0, 0, 'X');
        game.board.setPosition(1, 1, 'X');
        game.board.setPosition(2, 2, 'X');
        CHECK(game.isGameFinished() == 'X');
    }

    SUBCASE("Game is a draw") {
        game.board.setPosition(0, 0, 'X');
        game.board.setPosition(0, 1, 'O');
        game.board.setPosition(0, 2, 'X');
        game.board.setPosition(1, 0, 'X');
        game.board.setPosition(1, 1, 'X');
        game.board.setPosition(1, 2, 'O');
        game.board.setPosition(2, 0, 'O');
        game.board.setPosition(2, 1, 'X');
        game.board.setPosition(2, 2, 'O');
        CHECK(game.isGameFinished() == 'D');
    }
}

TEST_CASE("TTT::printBoard") {
    TTT game;

    std::cout << std::endl;
    game.printBoard();
}