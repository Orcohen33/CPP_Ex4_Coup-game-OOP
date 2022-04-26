#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "Captain.hpp"

using namespace std;

namespace coup
{
    Captain::Captain(Game &game, const std::string &name) : Player(game, name) {}
    void Captain::steal(Player &player){};
    void Captain::block(Player &player){};
}