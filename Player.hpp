#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "Game.hpp"

#pragma once

using namespace std;

namespace coup
{
    class Player
    {

    public:
        Player(Game &game, const string &name); // : Player.name(name)
        //{
        // game.addPlayer(this);
        //}
        string name;
        void income();
        void foreign_aid();
        virtual void coup(Player &player);

        int coins();           // getter
        virtual string role(); // getter
        int coin = 0;
    };
}