#ifndef SHIP_H
#define SHIP_H

#include "square.h"
#include <vector>

using namespace std;

namespace battleshipGame {

/**
 * @brief The Ship class represents a ship.
 *
 * Ship can be placed in 1, 2, 3 or 4 sequential squares.
 * It has a horizontal or a vertical orientation.
 * Start square is the leftmost or the topmost square accordingly.
 */
class Ship {

    vector<Square> squares; /**< squares in which ship placed */
    int hP; /**< ship's health points */

public:
    /**
     * Constructor. HP is setting equal to ship size.
     * @param startSquare - start square of the ship.
     * @param shipSize - ship's size.
     * @param horizontal
     */
    Ship(Square startSquare, int shipSize, bool horizontal);

    /**
     * @return Leftmost or topmost square of the ship.
     */
    Square getStartSquare() const;

    /**
     * @return Ship size.
     */
    int getSize() const;

    /**
     * @return True if ship is horizontal, false if ship is vertical.
     */
    bool isHorizontal() const;

    /**
     * @return Health points of the ship.
     */
    int getHP() const;

    /**
     * @param HP to set.
     */
    void setHP(int hP);

    /**
     * @return True if hp is equal to 0, false otherwise.
     */
    bool isSunk() const;

    /**
     * @return Sequence of squares in which ship is placed.
     */
    vector<Square> getSquares() const;
};

}

#endif // SHIP_H
