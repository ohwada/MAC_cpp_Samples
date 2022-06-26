#ifndef FLEET_H
#define FLEET_H

#include "ship.h"
#include "fire_result.h"
#include <vector>

using namespace std;

namespace battleshipGame {

/**
 * @brief The Fleet class represents player's fleet.
 *
 * Fleet can maximum consists of 4 single-decked, 3 two-decked,
 * 2 three-decked and 1 four-decked ships.
 * It keeps information about all squares states.
 */
class Fleet {

    vector<Ship> ships; /** set of ships */
    Square::State squaresState[10][10]; /** states of squares */

    /**
     * Checks if it's possible to place part of the ship
     * in the specified square.
     * @param square - square in which player are going to
     * place part of the ship.
     * @return
     */
    bool checkPositionForSquare(const Square& square) const;

public:
    /**
     * Default constructor.
     * By default all square states are NOT_ATTACKED.
     */
    Fleet();

    /**
     * Checks if it's possible to add the ship to the fleet
     * without collisions with other ships.
     * @param ship - ship to be adding
     * @return True if it's possible to add the ship, false otherwise.
     */
    bool checkPositionForShip(const Ship& ship) const;

    /**
     * Adds specified ship to the fleet.
     * @param ship - ship to be adding
     */
    void addShip(Ship ship);

    /**
     * Models the process of firing in specified square.
     * Sets state of the square to ATTACKED_WITH_SUCCESS, if there is
     * a ship in the square, otherwise the square state becomes ATTACKED.
     * In the first case it also sets states to ATTACKED for all
     * surounding squares to forbid player
     * to fire in obviously empty squares.
     * If there is a ship in the square, it's HP decreases by one.
     * @param square - square to be fired
     * @return Result of the fire.
     */
    FireResult fire(const Square& square);

    /**
     * @param square - square to be fired.
     * @return True if player can fire in the square, false otherwise.
     */
    bool hasAttacked(const Square& square) const;

    /**
     * @return Heath points of the fleet which is the sum of
     * health points of all ships in fleet.
     */
    int getHP() const;

    /**
     * Checks if there is no ship left with non zero HP.
     * @return True if fleet is destroyed, false otherwise.
     */
    bool isDestroyed() const;

    /**
     * @param x - x coordinate.
     * @param y - y coordinate.
     * @return State of the square with specified coordinates.
     */
    Square::State getSquareState(int x, int y) const;

    /**
     * @return Current ships set.
     */
    vector<Ship> getShips() const;

    /**
     * @return Index of the ship, which part placed in the specified square.
     */
    int findShipIndex(const Square& square) const;
};

}

#endif // FLEET_H
