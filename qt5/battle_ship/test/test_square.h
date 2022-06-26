#include <QtTest/QtTest>

class TestSquare: public QObject {

    Q_OBJECT

private slots:

    void testConstructor();
    void testGettersAndSetters();
    void testComparisonOperators();
    void testAssignmentOperator();
};
