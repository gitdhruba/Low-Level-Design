#ifndef PLAYER_HDR

#define PLAYER_HDR

#include <string>

class Player {
private:
    std::string name;
    int pos;

public:
    Player(const std::string &, int);
    ~Player();

    std::string getName() const;
    int getPos() const;

    void setPos(int);
};

#endif