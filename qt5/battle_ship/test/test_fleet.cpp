#include "test_fleet.h"
#include "fleet.h"

using namespace battleshipGame;

void TestFleet::testCreation() {
    Fleet fleet;
    Ship sh1(Square(1, 1), 2, true);
    Ship sh2(Square(3, 4), 1, true);
    Ship sh3(Square(6, 7), 3, false);
    fleet.addShip(sh1);
    fleet.addShip(sh2);
    fleet.addShip(sh3);
    QCOMPARE(fleet.getShips()[2].getSquares(), sh3.getSquares());
    QVERIFY(fleet.getHP() == 6);
    QVERIFY(fleet.findShipIndex(Square(2, 1)) == 0);
    QVERIFY(fleet.findShipIndex(Square(8, 8)) == -1);
}

void TestFleet::testCheckShip() {
    Fleet fleet;
    Ship sh1(Square(1, 1), 1, true);
    Ship sh2(Square(3, 3), 1, true);
    fleet.addShip(sh1);
    fleet.addShip(sh2);
    QVERIFY(!fleet.checkPositionForShip(Ship(Square(0, 1), 3, true)));
    QVERIFY(!fleet.checkPositionForShip(Ship(Square(2, 2), 1, true)));
    QVERIFY(!fleet.checkPositionForShip(Ship(Square(2, 2), 2, true)));
    QVERIFY(fleet.checkPositionForShip(Ship(Square(3, 1), 1, true)));
    QVERIFY(!fleet.checkPositionForShip(Ship(Square(6, 9), 2, false)));
    QVERIFY(!fleet.checkPositionForShip(Ship(Square(8, 7), 4, true)));
    QVERIFY(fleet.checkPositionForShip(Ship(Square(5, 5), 3, false)));
}

void TestFleet::testFire() {
    Fleet fleet;
    Ship sh1(Square(2, 3), 1, true);
    Ship sh2(Square(5, 5), 2, false);
    fleet.addShip(sh1);
    fleet.addShip(sh2);
    QVERIFY(fleet.getSquareState(3, 4) == Square::NOT_ATTACKED);
    fleet.fire(Square(2, 3));
    QVERIFY(fleet.getSquareState(3, 4) == Square::ATTACKED);
    QVERIFY(fleet.getSquareState(2, 2) == Square::ATTACKED);
    QVERIFY(fleet.getSquareState(2, 3) == Square::ATTACKED_WITH_SUCCESS);
    fleet.fire(Square(5, 6));
    QVERIFY(fleet.getSquareState(5, 6) == Square::ATTACKED_WITH_SUCCESS);
    QVERIFY(fleet.getSquareState(5, 5) == Square::NOT_ATTACKED);
    fleet.fire(Square(7, 9));
    QVERIFY(fleet.getSquareState(8, 9) == Square::NOT_ATTACKED);
    QVERIFY(fleet.getSquareState(7, 9) == Square::ATTACKED);
}
