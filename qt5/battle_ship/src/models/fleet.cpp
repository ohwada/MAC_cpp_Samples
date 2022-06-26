// change log
// 2022-06-01 K.OHWADA
// warning: comparison of integers of different signs


#include <iostream>
#include "fleet.h"
#include "fire_result.h"

using namespace std;
using namespace battleshipGame;

Fleet::Fleet() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            squaresState[i][j] = Square::NOT_ATTACKED;
        }
    }
}

int Fleet::findShipIndex(const Square& square) const {
    for (int i = 0; i < (int)ships.size(); i++) {
        for (int j = 0; j < (int)ships[i].getSquares().size(); j++) {
            if (ships[i].getSquares()[j] == square) {
                return i;
            }
        }
    }
    return -1;
}

bool Fleet::checkPositionForSquare(const Square& square) const {
    if (square.getX() < 0 || square.getX() >= 10 ||
        square.getY() < 0 || square.getY() >= 10 ||
        ~findShipIndex(square)) {
        return false;
    }

    for (int dX = -1; dX <= 1; dX++) {
        for (int dY = -1; dY <= 1; dY++) {
            if (!(dX || dY)) {
                continue;
            }

            Square currentSquare(square.getX() + dX, square.getY() + dY);
            if (currentSquare.getX() >= 0 && currentSquare.getX() < 10 &&
                currentSquare.getY() >= 0 && currentSquare.getY() < 10 &&
                ~findShipIndex(currentSquare)) {
                return false;
            }
        }
    }
    return true;
}

bool Fleet::checkPositionForShip(const Ship& ship) const {
    auto startSquare = ship.getStartSquare();
    auto shipSize = ship.getSize();
    auto horizontal = ship.isHorizontal();
    if (horizontal) {
        for (int x = startSquare.getX(); x < startSquare.getX() + shipSize; x++) {
            Square square(x, startSquare.getY());
            if (!checkPositionForSquare(square)) {
                return false;
            }
        }
    } else {
        for (int y = startSquare.getY(); y < startSquare.getY() + shipSize; y++) {
            Square square(startSquare.getX(), y);
            if (!checkPositionForSquare(square)) {
                return false;
            }
        }
    }
    return true;
}

void Fleet::addShip(Ship ship) {
    ships.push_back(ship);
}

FireResult Fleet::fire(const Square& square) {
    int attackedShip = findShipIndex(square);

    if (attackedShip == -1) {
        squaresState[square.getX()][square.getY()] = Square::ATTACKED;
        return FireResult::BESIDE;
    }

    squaresState[square.getX()][square.getY()] = Square::ATTACKED_WITH_SUCCESS;
    ships[attackedShip].setHP(ships[attackedShip].getHP() - 1);

    if (!ships[attackedShip].getHP()) {
        for (int i = 0; i < (int)ships[attackedShip].getSquares().size(); i++) {
            Square currentSquare = ships[attackedShip].getSquares()[i];
            for (int dX = -1; dX <= 1; dX++) {
                for (int dY = -1; dY <= 1; dY++) {
                    if (!(dX || dY)) {
                        continue;
                    }

                    Square adjacenctSquare(currentSquare.getX() + dX,
                                           currentSquare.getY() + dY);
                    if (adjacenctSquare.getX() >= 0 &&
                        adjacenctSquare.getX() < 10 &&
                        adjacenctSquare.getY() >= 0 &&
                        adjacenctSquare.getY() < 10 &&
                        squaresState[adjacenctSquare.getX()]
                                    [adjacenctSquare.getY()] !=
                        Square::ATTACKED_WITH_SUCCESS) {
                        squaresState[adjacenctSquare.getX()]
                                    [adjacenctSquare.getY()] = Square::ATTACKED;
                    }
                }
            }
        }
        return FireResult::SUNK;
    }
    if (ships[attackedShip].getSquares().size() -
               ships[attackedShip].getHP() >= 2) {
        bool orientation = ships[attackedShip].getSquares()[0].getY() ==
                           ships[attackedShip].getSquares()[1].getY();

        if (orientation) {
            for (int i = 0; i < ships[attackedShip].getSquares().size(); i++) {
                Square currentSquare = ships[attackedShip].getSquares()[i];
                if (squaresState[currentSquare.getX()][currentSquare.getY()] !=
                    Square::ATTACKED_WITH_SUCCESS) {
                    continue;
                }

                if (currentSquare.getY() != 0) {
                    squaresState[currentSquare.getX()][currentSquare.getY() - 1] = Square::ATTACKED;
                }
                if (currentSquare.getY() != 10 - 1) {
                    squaresState[currentSquare.getX()][currentSquare.getY() + 1] = Square::ATTACKED;
                }
            }
        } else {
            for (int i = 0; i < ships[attackedShip].getSquares().size(); i++) {
                Square currentSquare = ships[attackedShip].getSquares()[i];
                if (squaresState[currentSquare.getX()][currentSquare.getY()] !=
                    Square::ATTACKED_WITH_SUCCESS) {
                    continue;
                }

                if (currentSquare.getX() != 0) {
                    squaresState[currentSquare.getX() - 1][currentSquare.getY()] = Square::ATTACKED;
                }
                if (currentSquare.getX() != 10 - 1) {
                    squaresState[currentSquare.getX() + 1][currentSquare.getY()] = Square::ATTACKED;
                }
            }
        }
    }
    return FireResult::INJURED;
}

bool Fleet::hasAttacked(const Square& square) const {
    return squaresState[square.getX()][square.getY()] != Square::NOT_ATTACKED;
}

int Fleet::getHP() const {
    int sumHPs = 0;
    for (int i = 0; i < (int)ships.size(); i++) {
        sumHPs += ships[i].getHP();
    }
    return sumHPs;
}

bool Fleet::isDestroyed() const {
    return !getHP();
}

Square::State Fleet::getSquareState(int x, int y) const {
    return this->squaresState[x][y];
}

vector<Ship> Fleet::getShips() const {
    return this->ships;
}
