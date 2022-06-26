#include <QtTest/QtTest>
#include "test_square.h"
#include "test_ship.h"
#include "test_fleet.h"

int main(int argc, char* argv[]) {
    int status = 0;
    {
        TestSquare obj;
        status |= QTest::qExec(&obj, argc, argv);
    }
    {
        TestShip obj;
        status |= QTest::qExec(&obj, argc, argv);
    }
    {
        TestFleet obj;
        status |= QTest::qExec(&obj, argc, argv);
    }
    return status;
}
