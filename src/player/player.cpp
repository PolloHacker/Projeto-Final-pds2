#include <iostream>
#include "player.hpp"


Player::Player(int id, std::string name, std::string nickname, Stats stats): _id(id), _name(name), _nickname(nickname), _stats(stats) {}

Player::Player(int id, std::string name, std::string nickname): _id(id), _name(name), _nickname(nickname), _stats() {}

int Player::getId() const { return this->_id; }

Stats Player::getStats() const { return this->_stats; }

std::string Player::getNickname() const { return this->_nickname; }

std::string Player::getName() const { return this->_name; }

void Player::setNickname(std::string nickname) {
    this->_nickname = nickname;
}

void Player::setName(std::string name) {
    this->_name = name;
}

/**
 * @brief Updates the player's statistics based on the result of a game.
 *
 * @param result A character representing the result of the game:
 *               'W' for a win, 'L' for a loss, 'D' for a draw.
 * @param game A character representing the type of game played.
 *
 * @throws InvalidInputException if the result character is not 'W', 'L', or 'D'.
 */
void Player::updateStats(char result, char game) {
    switch (result) {
        case 'W':
            this->_stats.TotalWins++;
            this->updateGameStats(game, true);
            break;
        case 'L':
            this->_stats.TotalLoses++;
            this->updateGameStats(game, false);
            break;
        case 'D':
            break;
        default:
            throw InvalidInputException("[X] - Resultado invalido");
    }
}

/**
 * @brief Updates the game statistics for the player based on the game type and result.
 * 
 * @param game A character representing the game type:
 *             'T' for Tic-Tac-Toe,
 *             'L' for Connect Four (Lig4),
 *             'R' for Reversi.
 * @param isWin A boolean indicating whether the player won the game (true) or lost the game (false).
 */
void Player::updateGameStats(char game, bool isWin) {
    switch (game) {
        case 'T':
            isWin ? this->_stats.winsTTT++ : this->_stats.losesTTT++;
            break;
        case 'L':
            isWin ? this->_stats.winsLig4++ : this->_stats.losesLig4++;
            break;
        case 'R':
            isWin ? this->_stats.winsReversi++ : this->_stats.losesReversi++;
            break;
        default:
            break;
    }
}

std::ostream& operator<<(std::ostream& os, const Player& player) {
    os << "+---------------------------+\n" 
        << "ID do jogador: " << player.getId() << "\n"
        << "Nome: " << player.getName() << "\n"
        << "Apelido: " << player.getNickname() << "\n"
        << player.getStats()
        << "+---------------------------+\n";
    return os;
}