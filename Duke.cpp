#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "Duke.hpp"

using namespace std;

namespace coup
{
    /*
    Constructor for Duke
    */
    Duke::Duke(Game &game, const std::string &name) : Player(game, name){};

    // Duke(Game &game, const std::string &name) : Player(game, name){};
    void Duke::tax()
    {
        this->coin += 3;
    };
    void Duke::block(Player &player){};

}