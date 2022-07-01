/**
 * main.cpp
 * 2022-06-01 K.OHWADA
 */

// reference : http://qt-log.open-memo.net/sub/scroll-area--usage-of-scrollarea.html


#include <QApplication>
#include <QMainWindow>
#include <QScrollArea>
#include "TextView.h"


/**
 * main
 */
int main(int argc, char *argv[])
{
const QString TEXT( R"(
Mary had a little lamb,
Its fleece was white as snow,
And every where that Mary went
The lamb was sure to go
He followed her to school one day
That was against the rule,
It made the children laugh and play,
To see a lamb at school.)" );


// window size
const int W  = 320;
const int H  = 240;

// font size
const int S  = 24;


    QApplication a(argc, argv);

   QMainWindow *mainWin = new QMainWindow();

    mainWin->setGeometry(10, 10, W, H);

    mainWin->setWindowTitle("scroll area");

QScrollArea * scrollArea = new QScrollArea();
scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

//  always show vertical scrollbars
scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

   TextView *text_view = new TextView();

    float h = 2*H;
    text_view->setSceneSize(W, h);

    text_view->setFontSize(S);

    float w = 0.66 * W;
    text_view->setText( w, TEXT);
    QGraphicsView *view = text_view->getView();

    scrollArea->setWidget( view );

    mainWin->setCentralWidget(scrollArea);

    mainWin->show();

    return a.exec();
}