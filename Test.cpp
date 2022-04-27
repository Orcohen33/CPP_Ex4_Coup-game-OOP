#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

#include "doctest.h"
#include "Player.hpp"
#include "Duke.hpp"
#include "Contessa.hpp"
#include "Assassin.hpp"
#include "Captain.hpp"
#include "Ambassador.hpp"

using namespace std;
using namespace coup;

TEST_CASE("Check functions")
{
    SUBCASE("Duke functions")
    {
        Game game{};
        Duke duke{game, "Moshe"};
        Assassin assassin{game, "Yossi"};
        Ambassador ambassador{game, "Meirav"};

        duke.tax();
        CHECK(duke.coins() == 3);
        assassin.foreign_aid();       // 2 coins
        duke.block(assassin);         // assassin's foreign aid blocked
        CHECK(assassin.coins() == 0); // assassin coins = 0
    }
    SUBCASE("Assassin functions")
    {
        Game game{};
        Duke duke{game, "Moshe"};
        Assassin assassin{game, "Yossi"};
        Ambassador ambassador{game, "Meirav"};
        int total_players_before_coup = game.players().size();
        // round 1
        duke.income();
        assassin.income();
        ambassador.income();
        // round 2
        duke.income();
        assassin.foreign_aid();
        ambassador.income();
        // round 3
        duke.income();
        assassin.coup(duke);
        ambassador.income();
        int total_players_after_coup = game.players().size();
        CHECK(total_players_after_coup == total_players_before_coup - 1);
    }
    SUBCASE("Ambassador functions")
    {
        Game game{};
        Duke duke{game, "Moshe"};
        Assassin assassin{game, "Yossi"};
        Ambassador ambassador{game, "Meirav"};
        Captain captain{game, "Reut"};
        // round 1
        duke.income();       // 1 coin
        assassin.income();   // 1 coin
        ambassador.income(); // 1 coin
        captain.income();    // 1 coin
        // round 2
        duke.income();                       // 2 coins
        assassin.foreign_aid();              // 3 coins
        ambassador.transfer(assassin, duke); // transfer 1 coin from assassin to duke
        // Test if transfer function work
        CHECK(duke.coins() == 3);
        CHECK(assassin.coins() == 2);
        // Test if ambassador can block steal function
        captain.steal(duke);         // Captain steal 2 coins from duke, duke.coins() = 1.
        ambassador.block(captain);   // Ambassador block captain's steal function.
        CHECK(captain.coins() == 1); // Captain coins = 1 , Steal function doesn't work.
    }
    SUBCASE("Captain functions")
    {
        SUBCASE("steal 2 coins && block")
        {
            Game game{};
            Duke duke{game, "Moshe"};
            Assassin assassin{game, "Yossi"};
            Captain captain1{game, "Meirav"};
            Captain captain2{game, "Reut"};
            // round 1
            duke.income();     // 1 coin
            assassin.income(); // 1 coin
            captain1.income(); // 1 coin
            captain2.income(); // 1 coin
            // round 2
            duke.income();          // 2 coins
            assassin.foreign_aid(); // 3 coins
            captain1.steal(duke);   // 3 coins
            // Test if 'steal' function work
            CHECK(duke.coins() == 0);
            // Test if captain can block steal function
            captain2.block(captain1); // captain2 blocks captain1 steal function.
            CHECK(duke.coins() == 2);
            captain2.income(); // 2 coins
        }
        SUBCASE("steal 1 coin")
        {
            Game game{};
            Duke duke{game, "Moshe"};
            Assassin assassin{game, "Yossi"};
            Captain captain{game, "Meirav"};
            // ---------------------------- round 1 start ----------------------------
            duke.income();     // 1 coin
            assassin.income(); // 1 coin
            CHECK(duke.coins() == 1);
            captain.steal(duke); // 1 coin
            CHECK(duke.coins() == 0);
            CHECK(captain.coins() == 1);
            // ---------------------------- round 1 end ----------------------------
        }
        SUBCASE("steal 0 coin")
        {
            Game game{};
            Captain captain{game, "Meirav"};
            Duke duke{game, "Moshe"};
            Assassin assassin{game, "Yossi"};
            // ---------------------------- round 1 start ----------------------------
            captain.steal(duke); // 0 coin
            CHECK(captain.coins() == 0);
            duke.income();
            assassin.income();
            // ---------------------------- round 1 end ----------------------------
        }
    }
    SUBCASE("Contessa functions")
    {
        Game game{};
        Duke duke{game, "Moshe"};
        Assassin assassin{game, "Yossi"};
        Contessa contessa{game, "Meirav"};
        // round 1
        duke.income();          // 1 coin
        assassin.foreign_aid(); // 2 coins
        contessa.income();      // 1 coin
        // round 2
        duke.income();          // 2 coins
        assassin.foreign_aid(); // 4 coins
        contessa.income();      // 2 coins
        // round 3 - Test block function of contessa
        duke.income(); // 3 coins
        int total_players_before_coup = game.players().size();
        assassin.coup(duke); // 1 coin left (coup cost 3 coins)
        int total_players_after_coup = game.players().size();
        CHECK(total_players_after_coup == total_players_before_coup - 1);
        contessa.block(assassin); // contessa block assassin's coup function.
        int total_players_after_block = game.players().size();
        CHECK(total_players_after_block == total_players_before_coup);
        contessa.income(); // 3 coins
    }
}

TEST_CASE("Run game_1")
{
    Game game_1{};

    Duke duke{game_1, "Moshe"};
    Assassin assassin{game_1, "Yossi"};
    Ambassador ambassador{game_1, "Meirav"};
    Captain captain{game_1, "Reut"};
    Contessa contessa{game_1, "Gilad"};
    /*
        Game turns will be:
        1.Moshe
        2.Yossi
        3.Meirav
        4.Reut
        5.Gilad
    */
    // --------------------- Round 1 start ---------------------
    CHECK_NOTHROW(duke.income());       // 1 coin
    CHECK_NOTHROW(assassin.income());   // 1 coin
    CHECK_NOTHROW(ambassador.income()); // 1 coin
    CHECK_NOTHROW(captain.income());    // 1 coin
    CHECK_NOTHROW(contessa.income());   // 1 coin
    // invalid turn
    // throws exception, it is duke's turn now
    CHECK_THROWS(assassin.income());

    // Invalid winner
    // More than one player is alive
    CHECK_THROWS(game_1.winner());
    /*
        Summary:
        duke: 1 coin
        assassin: 1 coin
        ambassador: 1 coin
        captain: 1 coin
        contessa: 1 coin
    */

    // --------------------- Round 1 end ---------------------

    // ----------------------- Round 2 start -----------------------
    // Test duke's block function
    duke.tax();                   // 4 coins
    assassin.foreign_aid();       // 3 coins
    CHECK(assassin.coins() == 3); // assassin coins = 3
    duke.block(assassin);         // assassin's foreign aid blocked
    CHECK(assassin.coins() == 1); // assassin coins = 1

    // Invalid block
    // Ambassdor can block only steal skill
    CHECK_THROWS(ambassador.block(duke));

    // Test ambassador's transfer function
    ambassador.transfer(duke, assassin); // transfer 1 coin from duke to assassin
    CHECK(duke.coins() == 3);            // duke coins = 3 ( transfer to assassin)
    CHECK(assassin.coins() == 2);        // assassin coins = 2 (transfered from duke)

    // Test captain's steal function
    captain.steal(duke);         // Captain steal 2 coins from duke, duke.coins() = 1.
    CHECK(duke.coins() == 1);    // duke coins = 1 (stealed by captain)
    CHECK(captain.coins() == 3); // captain coins = 3 (stealed from duke)

    contessa.income(); // 2 coins
    /*
        Summary:
        duke: 1 coin
        assassin: 2 coins
        ambassador: 1 coin
        captain: 3 coins
        contessa: 2 coins
    */
    // ----------------------- Round 2 finished -----------------------
    // ----------------------- Round 3 start -----------------------
    duke.tax();               // 4 coins
    assassin.foreign_aid();   // 4 coins
    ambassador.foreign_aid(); // 3 coins
    captain.foreign_aid();    // 5 coins
    contessa.foreign_aid();   // 4 coins
    /*
        Summary:
        duke: 4 coin
        assassin: 4 coins
        ambassador: 3 coins
        captain: 5 coins
        contessa: 4 coins
    */
    // ----------------------- Round 3 finished -----------------------
    // ----------------------- Round 4 start -----------------------

    // Test contessa block function
    vector<string> players_before_coup = game_1.players(); // 5 players
    duke.tax();                                            // 7 coins
    assassin.coup(duke);                                   // 1 coin left (coup cost 3 coins)
    vector<string> players_after_coup = game_1.players();  // 4 players
    CHECK(players_after_coup.size() == players_before_coup.size() - 1);
    CHECK_THROWS(contessa.block(duke));                    // contessa can't block duke
    CHECK_NOTHROW(contessa.block(assassin));               // contessa can block assassin coup
    vector<string> players_after_block = game_1.players(); // 5 players
    CHECK(players_after_block.size() == players_before_coup.size());
    ambassador.foreign_aid(); //  5 coins
    captain.foreign_aid();    //  7 coins
    contessa.foreign_aid();   //  6 coins

    /*
        Summary:
        duke: 7 coins
        assassin: 1 coins
        ambassador: 5 coins
        captain: 7 coins
        contessa: 6 coins
    */
    // ----------------------- Round 4 finished -----------------------
    // ----------------------- Round 5 start -----------------------
    duke.coup(assassin);                   // 0 coins
    players_after_coup = game_1.players(); // 4 players
    CHECK(players_after_coup.size() == 4);
    ambassador.foreign_aid(); // 7 coins

    // Ambassador block captain's steal function
    captain.steal(ambassador);   // 9 coins
    ambassador.block(captain);   // ambassador block captain's steal function
    CHECK(captain.coins() == 7); // captain coins = 7 , his steal skill blocked
    contessa.foreign_aid();      // 8 coins

    // Duke block contessa's foreign aid function
    duke.block(contessa);         // duke block contessa's foreign aid function
    CHECK(contessa.coins() == 6); // contessa coins = 6 , his foreign aid blocked
    /*
        Summary:
        duke: 0 coins
        assassin: 0 coins - left game
        ambassador: 7 coins
        captain: 7 coins
        contessa: 6 coins
    */
    // ----------------------- Round 5 finished -----------------------
    // ----------------------- Round 6 start -----------------------
    duke.tax();          // 3 coins
    ambassador.income(); // 8 coins
    // Invalid block by duke
    CHECK_THROWS(duke.block(ambassador)); // cant block him because ambassador isnt foreign aid
    captain.steal(duke);                  // 9 coins
    contessa.foreign_aid();               // 8 coins
    /*
        Summary:
        duke: 3 coins
        assassin: 0 coins - left game
        ambassador: 8 coins
        captain: 9 coins
        contessa: 8 coins
    */
    // ----------------------- Round 6 finished -----------------------
    // ----------------------- Round 7 start -----------------------
    duke.tax();                // 6 coins
    ambassador.foreign_aid();  // 10 coins
    captain.steal(ambassador); // 11 coins, ambassador - 8 coins
    contessa.foreign_aid();    // 10 coins
    /*
        Summary:
        duke: 6 coins
        assassin: 0 coins - left game
        ambassador: 10 coins
        captain: 11 coins
        contessa: 10 coins
    */
    // ----------------------- Round 7 finished -----------------------
    // ----------------------- Round 8 start -----------------------
    // Throw exception if player have more than or equal to 10 coins and try to use other command that isnt coup
    players_before_coup = game_1.players();           // 4 players
    duke.tax();                                       // 8 coins
    CHECK_THROWS(ambassador.transfer(duke, captain)); // can only use coup command
    CHECK_THROWS(ambassador.income());                // can only use coup command
    CHECK_THROWS(ambassador.foreign_aid());           // can only use coup command
    CHECK_NOTHROW(ambassador.coup(duke));             // can use coup command , 7 coins
    players_after_coup = game_1.players();            // 3 players
    CHECK(players_after_coup.size() == players_before_coup.size() - 1);

    // Throw exception if player have more than or equal to 10 coins and try to use other command that isnt coup
    players_before_coup = game_1.players();  // 3 players
    CHECK_THROWS(captain.steal(ambassador)); // can only use coup command
    CHECK_THROWS(captain.income());          // can only use coup command
    CHECK_THROWS(captain.foreign_aid());     // can only use coup command
    // Valid command
    CHECK_NOTHROW(captain.coup(ambassador)); // can use coup command
    players_after_coup = game_1.players();   // 2 players
    CHECK(players_after_coup.size() == players_before_coup.size() - 1);

    // Throw exception when contessa try to block player that isnt assassin
    CHECK_THROWS(contessa.block(ambassador)); // contessa can't block duke

    // Throw exception if player have more than or equal to 10 coins and try to use other command that isnt coup
    players_before_coup = game_1.players(); // 2 players
    CHECK_THROWS(contessa.income());        // can only use coup command
    CHECK_THROWS(contessa.foreign_aid());   // can only use coup command
    // Valid command
    CHECK_NOTHROW(contessa.coup(ambassador)); // can use coup command
    players_after_coup = game_1.players();    // 1 players
    CHECK(players_after_coup.size() == players_before_coup.size() - 1);

    CHECK_NOTHROW(game_1.winner()); // check if game is finished
    CHECK_EQ(game_1.winner() == "Gilad", true);
    /*
        Summary:
        duke: left game
        assassin: left game
        ambassador: left game
        captain: left game
        contessa: winner
    */
}