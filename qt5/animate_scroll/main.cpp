/**
 * main.cpp
 * 2022-06-01 K.OHWADA
 */

#include <QApplication>
#include <QGraphicsRectItem>
#include <QTimer>
#include "MyView.h"


/**
 * main
 */
int main(int argc, char *argv[])
{
// scenne size
const float SW = 10000;
const float SH = 20000;

// rectangle size
const float RW = 100;
const float RH = 100;

// x position to start to animate
const int X = 200;

// timer
const int START = 1000; // 1000 msec (1 sec)




    QApplication a(argc, argv);

    QGraphicsScene scene(0, 0, SW, SH);
    MyView* view = new MyView(&scene);


    QGraphicsRectItem* pRect = new QGraphicsRectItem(0, 0, RW, RH);

// center of scene
    float cx = scene.width()/2;
    float cy = scene.height()/2;
    pRect->setPos(cx, cy);
   scene.addItem(pRect);


    // timer to wait for the window to appear, before starting to move
    QTimer* pTimer = new QTimer;
    pTimer->setSingleShot(true);

    QObject::connect(pTimer, &QTimer::timeout,[=](){
        view->centerOn(pRect); // centre on the rectangle
        view->AnimateBy(X);
        pTimer->deleteLater();
    });

    pTimer->start(START);

    view->show();

    return a.exec();
}
