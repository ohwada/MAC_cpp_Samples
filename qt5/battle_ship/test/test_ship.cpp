#include "test_ship.h"
#include "ship.h"

using namespace battleshipGame;

void TestShip::testConstructor() {
    Square stSq(1, 1);
    Ship ship1(stSq, 3, true);
    vector<Square> squares1 = {Square(1, 1), Square(2, 1), Square(3, 1)};
    QVERIFY(ship1.getSquares() == squares1);
    Ship ship2(stSq, 3, false);
    vector<Square> squares2 = {Square(1, 1), Square(1, 2), Square(1, 3)};
    QVERIFY(ship2.getSquares() == squares2);
}

void TestShip::testGettersAndSetters() {
    Square stSq(1, 2);
    Ship ship(stSq, 4, true);
    QCOMPARE(ship.getStartSquare(), stSq);
    QVERIFY(ship.isHorizontal());
    QVERIFY(!ship.isSunk());
    QVERIFY(ship.getHP() == 4);
    ship.setHP(2);
    QVERIFY(ship.getHP() == 2);
    ship.setHP(0);
    QVERIFY(ship.isSunk());
    QVERIFY(ship.getSize() == 4);
    Ship ship2(stSq, 2, false);
    QVERIFY(!ship2.isHorizontal());
}
