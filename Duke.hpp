#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "Player.hpp"

using namespace std;

namespace coup
{
    class Duke : public Player
    {
    public:
        Duke(Game &game, const std::string &name);
        void tax();
        void block(Player &player);
    };
}