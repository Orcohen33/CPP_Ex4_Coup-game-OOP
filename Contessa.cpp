#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "Contessa.hpp"

using namespace std;

namespace coup
{
    coup::Contessa::Contessa(Game &game, const std::string &name) : Player(game, name) {}
    void Contessa::block(Player &player){};
}