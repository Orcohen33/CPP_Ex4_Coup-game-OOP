#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "Ambassador.hpp"

using namespace std;

namespace coup
{
    Ambassador::Ambassador(Game &game, const std::string &name) : Player(game, name) {}
    void Ambassador::transfer(Player &player1, Player &player2)
    {
        if (player1.coins() == 0)
        {
            return;
        }
        else
        {
            player1.coin -= 1;
            player2.coin += 1;
        }
    };
    void Ambassador::block(Player &player){};
}