#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "board.hpp"

TEST_CASE("Board constructor and getters") {
    Board board(3, 3);
    CHECK(board.getRows() == 3);
    CHECK(board.getCols() == 3);
}

TEST_CASE("Board set and get element") {
    Board board(3, 3);
    board.setPosition(1, 1, 'X');
    CHECK(board.getElementAt(1, 1) == 'X');
}

TEST_CASE("Board isBoardFull") {
    Board board(2, 2);
    CHECK(board.isBoardFull() == false);
    board.setPosition(0, 0, 'X');
    board.setPosition(0, 1, 'O');
    board.setPosition(1, 0, 'X');
    board.setPosition(1, 1, 'O');
    CHECK(board.isBoardFull() == true);
}

TEST_CASE("Board isWithinBounds") {
    Board board(3, 3);
    CHECK(board.isWithinBounds(1, 1) == true);
    CHECK(board.isWithinBounds(3, 3) == false);
    CHECK(board.isWithinBounds(-1, 0) == false);
    CHECK(board.isWithinBounds(0, -1) == false);
}