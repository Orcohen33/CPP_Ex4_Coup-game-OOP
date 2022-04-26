#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "Player.hpp"

using namespace std;

namespace coup
{
    Player::Player(Game &game, const std::string &name) : name(name)
    {
        game.add_player(*this);
    }
    void Player::income()
    {
        Player::coin += 1;
    }
    void Player::foreign_aid()
    {
        Player::coin += 2;
    }
    // Coup other player , cost 7 coins
    void Player::coup(Player &player)
    {
        if (Player::coin < 7)
        {
            throw std::runtime_error("Not enough coins");
        }
        else
        {
            Player::coin -= 7;
        }
    }
    int Player::coins()
    {
        return Player::coin;
    }
    string Player::role()
    {
        return "Player";
    }
}