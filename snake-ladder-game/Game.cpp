#include "./Game.hpp"
#include "./Exception.hpp"

#include <iostream>
#include <new>
#include <sstream>

Game::Game(
    int _boardSize,
    int _diceSize,
    const std::vector<Player *> &_players,
    const std::vector<std::pair<int, int>> &snakes,
    const std::vector<std::pair<int, int>> &ladders
) {
    this->boardSize = _boardSize;
    this->diceSize = _diceSize;
    this->players = _players;

    try {
        this->board = new Board(this->boardSize);
        this->dice = new Dice(this->diceSize);
    }
    catch (const std::bad_alloc &e) {
        std::cerr << "error creatng board: " << e.what() << std::endl;
        throw *(new SnakeLadderException(std::string(e.what())));
    }

    for (auto &snake : snakes) {
        if (!board->placeSnake(snake.first, snake.second)) {
            std::stringstream ss;
            ss << "could not place snake at " << snake.first;
            throw *(new SnakeLadderException(ss.str()));
        }
    }

    for (auto &ladder : ladders) {
        if (!board->placeLadder(ladder.first, ladder.second)) {
            std::stringstream ss;
            ss << "could not place ladder at " << ladder.first;
            throw *(new SnakeLadderException(ss.str()));
        }
    }
}

Game::~Game() {
    if (board != nullptr) delete board;
    if (dice != nullptr) delete dice;
}

void Game::playGame() const {
    int n = (int)players.size();
    std::cout << "\nStarted ..... " << std::endl;
    for (int i = 0; i < n; i = (i + 1) % n) {
        std::cout << "Turn of Player " << i + 1 << " --> name: " << players[i]->getName() << std::endl;
        std::cout << "      current pos: " << players[i]->getPos() << " ";
        int diceValue = dice->roll();
        std::cout << "dice value: " << diceValue << " ";
        board->makeMove(*players[i], diceValue);
        std::cout << "next pos: " << players[i]->getPos() << std::endl;
        if (players[i]->getPos() == boardSize) {
            std::cout << " ---------- THE END ----------- " << std::endl;
            std::cout << players[i]->getName() << " won the game. " << std::endl;
            return;
        }
    }

    return;
}