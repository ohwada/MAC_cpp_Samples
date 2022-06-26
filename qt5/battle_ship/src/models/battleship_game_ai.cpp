// change log
// 2022-06-01 K.OHWADA
// warning: comparison of integers of different signs: 

#include "battleship_game_ai.h"

using namespace battleshipGame;
using namespace std;

void BattleshipGameAI::placeShips(
    Fleet& fleet, const map<int, int>& shipsMap) {
    int countsOfShips[5] = {0, shipsMap.at(1), shipsMap.at(2),
                            shipsMap.at(3), shipsMap.at(4)};

    for (int size = 4; size > 0; size--) {
        bool isOrientationFixed = false, horizontal;

        for (int i = 0; i < countsOfShips[size]; i++) {
            if (!isOrientationFixed) {
                horizontal = rand() % 2;
            }

            vector <Square> correctSquares;
            for (int x = 0; x < 10; x++) {
                for (int y = 0; y < 10; y++) {
                    Square square(x, y);
                    if (fleet.checkPositionForShip(
                          Ship(square, size, horizontal))) {
                        correctSquares.push_back(square);
                    }
                }
            }

            if (correctSquares.empty()) {
                isOrientationFixed = true;
                horizontal = !horizontal;
                i--;
                continue;
            }

            Ship ship(correctSquares[rand() % correctSquares.size()],
                      size, horizontal);
            fleet.addShip(ship);
            isOrientationFixed = false;
        }
    }
}

Square BattleshipGameAI::findBestSquare(const Fleet& fleet) {
    vector<Square> correctSquares;
    vector<Square> goodSquares;
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            Square square(x, y);
            if (!fleet.hasAttacked(square)) {
                correctSquares.push_back(square);
                if (isSquareGood(fleet, square)) {
                    goodSquares.push_back(square);
                }
            }
        }
    }
    if (goodSquares.empty()) {
        return correctSquares[rand() % correctSquares.size()];
    } else {
        return goodSquares[rand() % goodSquares.size()];
    }
}

bool BattleshipGameAI::isSquareGood(const Fleet& fleet, const Square& square) {
    Square squares[4] = {Square :: makeSquare(square.getX(), square.getY() - 1),
                         Square :: makeSquare(square.getX(), square.getY() + 1),
                         Square :: makeSquare(square.getX() - 1, square.getY()),
                         Square :: makeSquare(square.getX() + 1, square.getY())};

    bool isInjuriedShip[4];
    for (int i = 0; i < 4; i++) {
        int shipIndex = fleet.findShipIndex(squares[i]);

        if (!~shipIndex) {
            isInjuriedShip[i] = false;
            continue;
        }

        Ship ship = fleet.getShips()[shipIndex];

        isInjuriedShip[i] = ship.getHP() != (int)ship.getSquares().size() &&
                            ship.getHP() != 0 &&
                            fleet.getSquareState(squares[i].getX(),
                                                     squares[i].getY()) ==
                                                     Square::ATTACKED_WITH_SUCCESS;
    }

    return isInjuriedShip[0] || isInjuriedShip[1] ||
           isInjuriedShip[2] || isInjuriedShip[3];
}
