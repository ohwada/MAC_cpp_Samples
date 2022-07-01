/**
 * main.cpp
 * 2022-06-01 K.OHWADA
 */

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "movable_rect_item.h"

/**
 * main
 */
int main(int argc, char *argv[])
{
// scenne size
const float SX = 0;
const float SY = 0;
const float SW = 320;
const float SH = 240;


    QApplication app(argc, argv);

    QGraphicsScene scene(SX, SY, SW, SH);

    MovableRectItem item;

    float cx = SW/2;
    float cy = SH/2;

    item.setPos(cx, cy);

    scene.addItem(&item);

    QGraphicsView *view  = new QGraphicsView(&scene);

    view->show();

    return app.exec();
}

