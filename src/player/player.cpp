#include <iostream>
#include "player.hpp"


Player::Player(std::string nickname, std::string name): _stats(), _nickname(nickname), _name(name), _id(this->num_players++) {
    this->_nickname = nickname;
    this->_name = name;
}

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

std::ostream& operator<<(std::ostream& os, const Player& player) {
    os << "Player ID: " << player.getId() << "\n"
        << "Nickname: " << player.getNickname() << "\n"
        << "Name: " << player.getName() << "\n"
        << "Stats: " << player.getStats();
    return os;
}

int Player::num_players = 0;