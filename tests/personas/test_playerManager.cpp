#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <fstream>
#include "playerManager.hpp"
#include "player.hpp"

TEST_CASE("Add Player") {
    PlayerManager pm;

    SUBCASE("Add a new player") {
        pm.addPlayer("name", "nickname1");
        CHECK(pm.getPlayerCount() == 1);
    }

    SUBCASE("Add a player with duplicate nickname") {
        pm.addPlayer("name", "nickname1");
        CHECK_THROWS_AS(pm.addPlayer("name", "nickname1"), PlayerAlreadyExistsException);
        CHECK(pm.getPlayerCount() == 1);
    }
}

TEST_CASE("Remove Player") {
    PlayerManager pm;
    pm.addPlayer("name", "nickname1");

    SUBCASE("Remove an existing player") {
        pm.removePlayer("nickname1");
        CHECK(pm.getPlayerCount() == 0);
    }

    SUBCASE("Remove a non-existing player") {
        CHECK_THROWS_AS(pm.removePlayer("nickname2"), InexistentPlayerException);
        CHECK(pm.getPlayerCount() == 1);
    }
}

TEST_CASE("Retrieve Player Information") {
    PlayerManager pm;
    pm.addPlayer("name", "nickname1");

    SUBCASE("Retrieve an existing player") {
        Player player = *pm.getPlayer("nickname1");
        CHECK(player.getNickname() == "nickname1");
        CHECK(player.getName() == "name");
    }

    SUBCASE("Retrieve a non-existing player") {
        CHECK_THROWS_AS(pm.getPlayer("nickname2"), PlayerNotInListException);
    }
}

TEST_CASE("Edge Cases") {
    PlayerManager pm;

    SUBCASE("Retrieve information when the player list is empty") {
        CHECK_THROWS_AS(pm.getPlayer("nickname1"), PlayerNotInListException);
    }

    SUBCASE("Handle a large number of players") {
        for (int i = 0; i < 10000; ++i) {
            pm.addPlayer("TODO MUNDO IGUAL ", "nickname" + std::to_string(i));
        }
        CHECK(pm.getPlayerCount() == 10000);
    }

    SUBCASE("Handle invalid input formats") {
        // name
        CHECK_THROWS_AS(pm.addPlayer("", "nickname1"), InvalidInputException);
        CHECK_THROWS_AS(pm.addPlayer("nome1", "nickname1"), InvalidInputException);
        CHECK_THROWS_AS(pm.addPlayer("nome@", "nickname1"), InvalidInputException);

        CHECK_NOTHROW(pm.addPlayer("nome jogador", "nickname"));
        CHECK_NOTHROW(pm.addPlayer("Nome Jogador", "nickname12"));

        //nickname
        CHECK_THROWS_AS(pm.addPlayer("name", ""), InvalidInputException);
        CHECK_THROWS_AS(pm.addPlayer("name", "nickname@"), InvalidInputException);
        CHECK_THROWS_AS(pm.addPlayer("name", "nick name"), InvalidInputException);

        CHECK_NOTHROW(pm.addPlayer("nome", "nickname1"));
        CHECK_NOTHROW(pm.addPlayer("Nome", "nickname4214"));
        CHECK_NOTHROW(pm.addPlayer("Name", "Nickname1"));
    }
}

TEST_CASE("Load Players from File") {
    PlayerManager pm;

    // Create a temporary file with player data
    std::ofstream file("test_players.csv");
    file << "id,name,nickname,totalWins,winsTTT,winsLig4,winsReversi,totalLoses,losesTTT,losesLig4,losesReversi\n";
    file << "1,pera voadora,nickname1,10,3,4,3,5,2,1,2\n";
    file << "2,joao bobo,nickname2,20,5,7,8,10,3,4,3\n";
    file.close();

    pm.loadPlayers("test_players.csv");

    SUBCASE("Check loaded players") {
        CHECK(pm.getPlayerCount() == 2);

        Player player1 = *pm.getPlayer("nickname1");
        CHECK(player1.getName() == "pera voadora");
        CHECK(player1.getStats().TotalWins == 10);
        CHECK(player1.getStats().winsTTT == 3);
        CHECK(player1.getStats().winsLig4 == 4);
        CHECK(player1.getStats().winsReversi == 3);
        CHECK(player1.getStats().TotalLoses == 5);
        CHECK(player1.getStats().losesTTT == 2);
        CHECK(player1.getStats().losesLig4 == 1);
        CHECK(player1.getStats().losesReversi == 2);

        Player player2 = *pm.getPlayer("nickname2");
        CHECK(player2.getName() == "joao bobo");
        CHECK(player2.getStats().TotalWins == 20);
        CHECK(player2.getStats().winsTTT == 5);
        CHECK(player2.getStats().winsLig4 == 7);
        CHECK(player2.getStats().winsReversi == 8);
        CHECK(player2.getStats().TotalLoses == 10);
        CHECK(player2.getStats().losesTTT == 3);
        CHECK(player2.getStats().losesLig4 == 4);
        CHECK(player2.getStats().losesReversi == 3);
    }

    // Clean up the temporary file
    std::remove("test_players.csv");
}
