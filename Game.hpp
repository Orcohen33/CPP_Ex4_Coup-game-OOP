#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

#pragma once
using namespace std;

namespace coup
{
    class Player;
    class Game
    {
    public:
        Game();
        void add_player(Player &player);
        vector<string> players();
        string turn();
        string winner();

    private:
        vector<Player *> playerss;
        string turnn;
    };
}