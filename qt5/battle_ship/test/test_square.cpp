#include "test_square.h"
#include "square.h"

using namespace battleshipGame;

void TestSquare::testConstructor() {
    Square sq(3, 5);
    QVERIFY(sq.getX() == 3);
    QVERIFY(sq.getY() == 5);
}

void TestSquare::testGettersAndSetters() {
    Square sq = Square::makeSquare(2, 7);
    QCOMPARE(sq, Square(2, 7));
    sq.setX(1);
    sq.setY(3);
    QCOMPARE(sq, Square(1, 3));
}

void TestSquare::testComparisonOperators() {
    Square sq1(2, 4);
    Square sq2(1, 3);
    Square sq3(2, 4);
    QVERIFY(sq1 == sq3);
    QVERIFY(sq1 != sq2);
    QVERIFY(sq2 != sq3);
    QVERIFY(sq3 == sq1);
    QVERIFY(sq2 != sq1);
    QVERIFY(sq3 != sq2);
}

void TestSquare::testAssignmentOperator() {
    Square sq1(3, 4);
    Square sq2 = sq1;
    QCOMPARE(sq1, sq2);
    Square sq3(1, 2);
    sq1 = sq2 = sq3;
    QCOMPARE(sq1, sq3);
    QCOMPARE(sq1, sq2);
}
