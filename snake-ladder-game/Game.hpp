#ifndef GAME_HDR

#define GAME_HDR

#include "./Board.hpp"
#include "./Dice.hpp"

#include <vector>

class Game {
private:
    int boardSize;
    int diceSize;
    Board *board;
    Dice *dice;
    std::vector<Player *> players;

public:
    Game(
         int,
         int,
         const std::vector<Player *>&,
         const std::vector<std::pair<int, int>>&,
         const std::vector<std::pair<int, int>>&
        );

    ~Game();

    void playGame() const;
};

#endif