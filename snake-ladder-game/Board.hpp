#ifndef BOARD_HDR

#define BOARD_HDR

#include <vector>

#include "./BoardEntity.hpp"
#include "./Player.hpp"

class Board {
private:
    int n;
    std::vector<BoardEntity *> board;

    bool isValidPos(int pos) const {
        return ((pos > 0) && (pos <= n));
    }

public:
    Board(int);
    ~Board();

    bool placeSnake(int, int);
    
    bool placeLadder(int, int);

    void makeMove(Player &, int);
};

#endif
