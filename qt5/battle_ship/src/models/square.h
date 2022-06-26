#ifndef SQUARE_H
#define SQUARE_H

namespace battleshipGame {

/**
 * @brief The Square class represents a board cell.
 *
 * Square has two coordinates x and y in range from 0 to 9 inclusively.
 * Square can be in 3 different states.
 */
class Square {

    int x; /**< horizontal coordinate */
    int y; /**< vertical coordinate */

public:
    /**
     * This enum defines the valid states of Square.
     */
    enum State {
        NOT_ATTACKED, /**< Player can fire. */
        ATTACKED, ///< Player can not fire and
                  ///< there is no ship in this square.
        ATTACKED_WITH_SUCCESS ///< Player can not fire and
                              ///< there is a ship in this square.
    };

    /**
     * Defalt constructor.
     */
    Square() = default;

    /**
     * Constructor that initializes the coordinates.
     * @param x - horizontal coordinate.
     * @param y - vertical coordinate.
     */
    Square(int x, int y);

    /**
     * Makes square from two coordinates.
     * @param x - horizontal coordinate.
     * @param y - vertical coordinate.
     * @return Square(x, y).
     */
    static Square makeSquare(int x, int y);

    /**
     * @return Current x coordinate.
     */
    int getX() const;

    /**
     * @param x - x to set.
     */
    void setX(int x);

    /**
     * @return Current y coordinate.
     */
    int getY() const;

    /**
     * @param y - y to set.
     */
    void setY(int y);

    /**
     * Checks equality of two squares.
     * @return True if squares are equal, false otherwise.
     */
    bool operator == (const Square& other) const;

    /**
     * Checks inequality of two squares.
     * @param other - a Square object.
     * @return True if squares different, false otherwise.
     */
    bool operator != (const Square& other) const;

    /**
     * Assings a new square to the current.
     * @param other - a Square object.
     * @return *this.
     */
    Square& operator=(const Square& other);
};

}

#endif // SQUARE_H
