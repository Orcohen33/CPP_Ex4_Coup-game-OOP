#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "Player.hpp"

namespace coup
{
    class Ambassador : public Player
    {
    public:
        Ambassador(Game &game, const std::string &name);
        void transfer(Player &player1, Player &player2);
        // TODO : Maybe switch captain with player object
        void block(Player &player);
    };
}