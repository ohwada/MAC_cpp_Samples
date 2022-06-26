/** @file */

#ifndef SHOT_H
#define SHOT_H

namespace battleshipGame {

/**
 * The Shot enum defines 3 valid results of the fire.
 */
enum FireResult {
    BESIDE, /**< There isn't a ship in the square that was fired. */
    INJURED, ///< There is a ship in the square that was fired, but
             ///< after the fire it is not sunk.
    SUNK, ///< There is a ship in the square that was fired and
          ///< after the fire it is sunk.
};

}

#endif // SHOT_H
