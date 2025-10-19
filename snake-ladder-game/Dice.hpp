#ifndef DICE_HDR

#define DICE_HDR

#include <cstdlib>
#include <ctime>

class Dice {
private:
    int diceSize;

public:
    Dice(int);
    ~Dice();

    int roll();
};

#endif