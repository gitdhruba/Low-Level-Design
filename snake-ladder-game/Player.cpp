#include "./Player.hpp"

Player::Player(const std::string &_name, int _pos) {
    this->name = _name;
    this->pos  = _pos;
}

Player::~Player() {}

std::string Player::getName() const {
    return this->name;
}

int Player::getPos() const {
    return this->pos;
}

void Player::setPos(int pos) {
    this->pos = pos;
}