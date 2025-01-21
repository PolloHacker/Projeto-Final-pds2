#include <iostream>
#include "player.hpp"


Player::Player(int id, std::string name, std::string nickname, Stats stats): _stats(stats), _nickname(nickname), _name(name), _id(id) {}

Player::Player(int id, std::string name, std::string nickname): _stats(), _nickname(nickname), _name(name), _id(id) {}

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