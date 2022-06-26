#ifndef BATTLESHIP_GAME
#define BATTLESHIP_GAME

#include "fleet.h"
#include <map>
#include <memory>

using namespace std;

namespace battleshipGame {

/**
 * @brief The BattleshipGame class keeps all information about the game.
 *
 * The class uses Singleton design pattern.
 */
class BattleshipGame {

    shared_ptr<Fleet> yourFleet; /**< human player's fleet */
    shared_ptr<Fleet> opponentFleet; /**< machine player's fleet */

    /**
      * Default constructor is private.
      */
    BattleshipGame() = default;

public:
    /**
     * @brief The Mode enum defines valid modes of the game.
     */
    enum class Mode {
        PLACING, /**< Human player is placing it's ships */
        BATTLE, /**< Main mode, when players attack fleets of each other. */
        RESUME /**< Period after got a winner */
    };

    Mode mode; /**< Current game mode. */
    Square square; /**< Selected by human square in PLACING or BATTLE mode. */
    bool squareSelected; /**< Is square selected. */
    int shipSize;/**< Selected ship's size in PLACING mode. */
    bool shipHorizontal; /**< Is selected ship's orienatation horizontal. */
    bool stepYours; /**< Is step yours in BATTLE mode. */
    bool youWon; /**<  Is you the winner, informative only in RESUME mode. */
    map<int, int> shipsLeft; ///< Map of left to place ships
                             ///< in PLACING mode.

    /**
     * Starts game with specified number of ships for each decks number.
     * @param shipsMap - number of decks to number of ships map.
     */
    void start(const map<int, int>& shipsMap);

    /**
     * Finishes game.
     */
    void finish();

    /**
     * @param yours - Is fleet human's.
     * @return Human's or machine's fleet according to parameter yours.
     */
    Fleet& getFleet(bool yours);

    /**
     * @return Current game.
     */
    static BattleshipGame& get();

    /**
     * Deleted copy constructor.
     */
    BattleshipGame& operator=(BattleshipGame&) = delete;

    /**
     * Deleted copy constructor.
     */
    BattleshipGame& operator=(BattleshipGame&&) = delete;
};

}

#endif // BATTLESHIP_GAME
