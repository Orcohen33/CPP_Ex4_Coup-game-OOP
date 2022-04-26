#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "Game.hpp"

using namespace std;

namespace coup
{
    Game::Game() {}
    void Game::add_player(Player &player)
    {
        Game::playerss.push_back(&player);
    }
    vector<string> Game::players()
    {
        vector<string> players_vec;
        return players_vec;
    }
    string Game::turn()
    {
        return "";
    }
    string Game::winner()
    {
        return "";
    }
}