/**
 * main.cpp
 * 2022-06-01 K.OHWADA
 */

// reference : https://www.qt.io/ja-jp/blog/2010/05/21/qwidget

#include <QApplication>
#include "example.h"

/**
 * main
 */
int main(int argc, char *argv[])
{

    QApplication a(argc, argv); 

    Example w;    

    w.show();  

    return a.exec();    

}

