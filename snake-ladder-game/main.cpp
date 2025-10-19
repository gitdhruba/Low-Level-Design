#include "./Game.hpp"
#include "./Exception.hpp"
#include "./Player.hpp"

#include <iostream>
#include <vector>
#include <new>
#include <string>

using namespace std;

int main() {
    int boardSize, noOfPlayers, diceSize;
    cout << "Enter board-size, no-of-players and dice-size respectively: " << endl;
    cin >> boardSize >> noOfPlayers >> diceSize;

    cout << "Enter names of " << noOfPlayers << " players one by one: " << endl;
    vector<Player *> players(noOfPlayers);
    for (int i = 0; i < noOfPlayers; i++) {
        string name;
        cin >> name;
        try {
            players[i] = new Player(name, 1);
        }
        catch(std::bad_alloc &e) {
            std::cerr << "error creatng player: " << e.what() << std::endl;
            return 1;
        }
    }

    int noOfSnakes, noOfLadders;
    cout << "Enter no-of-snakes and no-of-ladders respectively : " << endl;
    cin >> noOfSnakes >> noOfLadders;
    vector<pair<int, int>> snakes(noOfSnakes), ladders(noOfLadders);
    cout << "Enter start and stop of " << noOfSnakes << " snakes one by one : " << endl;
    for (int i = 0; i < noOfSnakes; i++) cin >> snakes[i].first >> snakes[i].second;
    cout << "Enter start and stop of " << noOfLadders << " ladders one by one : " << endl;
    for (int i = 0; i < noOfLadders; i++) cin >> ladders[i].first >> ladders[i].second;


    Game *game = nullptr;
    try {
        game = new Game(
                        boardSize,
                        diceSize,
                        players,
                        snakes,
                        ladders
                    );

        game->playGame();
    }
    catch (SnakeLadderException &e) {
        cerr << e.what() << endl;
        return 1;
    }
    catch (exception &e) {
        cerr << e.what() << endl;
        return 1;
    }

    if (game != nullptr) delete game;

    for (int i = 0; i < noOfPlayers; i++) {
        if (players[i] != nullptr) {
            delete players[i];
        }
    }

    return 0;
}