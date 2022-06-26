#include <QtTest/QtTest>

class TestFleet: public QObject {

    Q_OBJECT

private slots:

    void testCreation();
    void testCheckShip();
    void testFire();
};
