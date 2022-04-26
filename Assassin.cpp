#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "Assassin.hpp"

using namespace std;

namespace coup
{
    Assassin::Assassin(Game &game, const std::string &name) : Player(game, name) {}
    void Assassin::coup(Player &player){};
}