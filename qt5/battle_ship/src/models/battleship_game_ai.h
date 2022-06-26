#ifndef BATTLESHIP_GAME_AI_H
#define BATTLESHIP_GAME_AI_H

#include "fleet.h"
#include <map>

using namespace std;

namespace battleshipGame {

/**
 * @brief The BattleshipGameAI class represents this game's
 * artificial inteligence.
 *
 * It contains methods for random placing of ships in the fleet and
 * for making the best machine step according to current
 * human fleet's state.
 */
class BattleshipGameAI {

    /**
     * @return True if  specified square better to fire than
     * other possible squares to fire in the fleet, false otherwise.
     */
    static bool isSquareGood(const Fleet& fleet, const Square& square);

public:
    /**
     * Places ships in specified fleet without collisions.
     * @param fleet - fleet to build.
     * @param shipsMap - decks to ships map.
     */
    static void placeShips(Fleet& fleet, const map<int, int>& shipsMap);

    /**
     * @param fleet - fleet to analyse.
     * @return Best square to fire according to the fleet's state.
     */
    static Square findBestSquare(const Fleet& fleet);
};

}

#endif // BATTLESHIP_GAME_AI_H
