/**
 * hello.cpp
 * hello window
 * 2022-06-01 K.OHWADA
 */

// refference : https://www.webcyou.com/?p=10581

#include <QApplication>
#include <QMainWindow>
#include "TextView.h"


/**
 * main
 */
int main(int argc, char** argv)
{
const QString HELLO("Hello World!!");
 
// window size
const int W  = 320;
const int H  = 240;

// font size
const int S  = 24;

    QApplication app(argc, argv);

    QMainWindow *mainWin = new QMainWindow();

    mainWin->setGeometry(10, 10, W, H);

    mainWin->setWindowTitle("hello");

   TextView *text_view = new TextView();

    text_view->setFontSize(S);

    int x = W/2;
    int y = H/2;

    text_view->setText( x, y, HELLO);

    QGraphicsView *view = text_view->getView();

    mainWin->setCentralWidget(view);

    mainWin->show();

    return app.exec();
}

