#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "Player.hpp"

using namespace std;

namespace coup
{
    class Captain : public Player
    {
    public:
        Captain(Game &game, const std::string &name);
        void steal(Player &player);
        void block(Player &player);
    };
}