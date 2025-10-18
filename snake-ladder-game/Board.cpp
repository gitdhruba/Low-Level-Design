#include "./Board.hpp"

#include <new>
#include <iostream>


Board::Board(int _n) {
    this->n = _n;
    board.resize(n + 1, nullptr);
    for (int i = 0; i <= n; i++) {
        try {
            board[i] = new BoardEntity(
                            BoardEntityType::NORMAL,        // type
                            i,                              // start
                            i                               // end
                        );
        }
        catch (const std::bad_alloc &e) {
            std::cerr << "error creatng board: " << e.what() << std::endl;
            throw e;
        }
    }
}

Board::~Board() {
    for (auto &ptr : board) {
        if (ptr != nullptr) {
            delete ptr;
            ptr = nullptr;
        }
    }
}

bool Board::placeSnake(int start, int end) {
    if (
        !isValidPos(start) ||
        !isValidPos(end)   ||
        (start <= end)     ||
        (board[start] == nullptr) ||
        (board[start]->getType() != BoardEntityType::NORMAL)
    ) return false;

    board[start]->setType(BoardEntityType::SNAKE);
    board[start]->setEnd(end);
    return true;
}

bool Board::placeLadder(int start, int end) {
    if (
        !isValidPos(start) ||
        !isValidPos(end)   ||
        (start >= end)     ||
        (board[start] == nullptr) ||
        (board[start]->getType() != BoardEntityType::NORMAL)
    ) return false;

    board[start]->setType(BoardEntityType::LADDER);
    board[start]->setEnd(end);
    return true;
}

void Board::makeMove(Player &player, int del) {
    int currpos = player.getPos() + del;
    if (!isValidPos(currpos)) return;

    while (board[currpos]->getType() != BoardEntityType::NORMAL) {
        currpos = board[currpos]->getEnd();
    }

    player.setPos(currpos);
    return;
}