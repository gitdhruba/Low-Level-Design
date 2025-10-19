#include "./Dice.hpp"

Dice::Dice(int _diceSize) {
    this->diceSize = _diceSize;
    srand(time(nullptr));
}

Dice::~Dice() {}

int Dice::roll() {
    return (rand() % diceSize) + 1;
}