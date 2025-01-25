#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <sstream>
#include "exec_utils.hpp"
#include "playerManager.hpp"

TEST_CASE("ExecUtils::listFilesInDirectory") {
    
    CHECK_THROWS_MESSAGE(ExecUtils::listFilesInDirectory("./input"), "in.csv\nteste.txt\n");
}

TEST_CASE("ExecUtils::handleLoadPlayers") {
    PlayerManager pm;
    std::istringstream iss("test_file.csv\n");
    std::streambuf* p_cin_streambuf = std::cin.rdbuf();
    std::cin.rdbuf(iss.rdbuf());

    ExecUtils::handleLoadPlayers(pm);

    std::cin.rdbuf(p_cin_streambuf);
    // Add checks to verify that players were loaded correctly
}

TEST_CASE("ExecUtils::handleCreatePlayer") {
    PlayerManager pm;
    std::istringstream iss("nickname name\n");
    std::streambuf* p_cin_streambuf = std::cin.rdbuf();
    std::cin.rdbuf(iss.rdbuf());

    ExecUtils::handleCreatePlayer(pm);

    std::cin.rdbuf(p_cin_streambuf);
    // Add checks to verify that the player was created correctly
}

TEST_CASE("ExecUtils::handleRemovePlayer") {
    PlayerManager pm;
    pm.addPlayer("name", "nickname");
    std::istringstream iss("nickname\n");
    std::streambuf* p_cin_streambuf = std::cin.rdbuf();
    std::cin.rdbuf(iss.rdbuf());

    ExecUtils::handleRemovePlayer(pm);

    std::cin.rdbuf(p_cin_streambuf);
    // Add checks to verify that the player was removed correctly
}

TEST_CASE("ExecUtils::handleListPlayers") {
    PlayerManager pm;
    pm.addPlayer("name1", "nickname1");
    pm.addPlayer("name2", "nickname2");

    std::istringstream iss("C\n");
    std::streambuf* p_cin_streambuf = std::cin.rdbuf();
    std::cin.rdbuf(iss.rdbuf());

    std::ostringstream oss;
    std::streambuf* p_cout_streambuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());

    ExecUtils::handleListPlayers(pm);

    std::cin.rdbuf(p_cin_streambuf);
    std::cout.rdbuf(p_cout_streambuf);
    // Add checks to verify that the players were listed correctly
}

TEST_CASE("ExecUtils::handlePlayGame") {
    PlayerManager pm;
    pm.addPlayer("name1", "nickname1");
    pm.addPlayer("name2", "nickname2");

    std::istringstream iss("R\nnickname1\nnickname2\n");
    std::streambuf* p_cin_streambuf = std::cin.rdbuf();
    std::cin.rdbuf(iss.rdbuf());

    std::ostringstream oss;
    std::streambuf* p_cout_streambuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());

    ExecUtils::handlePlayGame(pm);

    std::cin.rdbuf(p_cin_streambuf);
    std::cout.rdbuf(p_cout_streambuf);
    // Add checks to verify that the game was played correctly
}