#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "player.hpp"

TEST_CASE("Testing Player class") {
    Player player1("nickname1", "name1");
    Player player2("nickname2", "name2");

    SUBCASE("Test getId") {
        CHECK(player1.getId() == 0);
        CHECK(player2.getId() == 1);
    }

    SUBCASE("Test getNickname") {
        CHECK(player1.getNickname() == "nickname1");
        CHECK(player2.getNickname() == "nickname2");
    }

    SUBCASE("Test getName") {
        CHECK(player1.getName() == "name1");
        CHECK(player2.getName() == "name2");
    }

    SUBCASE("Test getStats") {
        Stats stats1 = player1.getStats();
        Stats stats2 = player2.getStats();
        CHECK(stats1 == Stats());
        CHECK(stats2 == Stats());
    }

    SUBCASE("Test setNickname") {
        player1.setNickname("new_nickname1");
        CHECK(player1.getNickname() == "new_nickname1");
    }

    SUBCASE("Test setName") {
        player1.setName("new_name1");
        CHECK(player1.getName() == "new_name1");
    }

    SUBCASE("Test operator<<") {
        std::ostringstream oss;
        oss << player1;
        std::string output = oss.str();
        CHECK(output.find("nickname1") != std::string::npos);
        CHECK(output.find("name1") != std::string::npos);
    }
}
