/**
 * MainWindpw.cpp
 * draw rectangle in GraphicView
 * 2022-06-01 K.OHWADA
 */

// refference : http://vivi.dyndns.org/vivi/docs/Qt/graphics.html

// #include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QRect>
#include <QPen>
#include <QBrush>
#include "MainWindow.h"


/**
 *  constractor
 */
MainWindow::MainWindow()
    : QMainWindow()
{
    QGraphicsScene *m_scene = new QGraphicsScene(QRect(0, 0, 320, 240));

// a little smaller than the scene
    m_scene->addRect(10, 10, 300, 220, QPen(Qt::black, 5), QBrush(Qt::white)); 

    QGraphicsView *m_view = new QGraphicsView(m_scene);
    m_view->setBackgroundBrush(QBrush(Qt::gray));

    setCentralWidget(m_view);
}
