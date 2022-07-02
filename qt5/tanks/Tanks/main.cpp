/**
 * main.cpp
 * 2022-06-01 K.OHWADA
 */

// original : https://github.com/magziim/Tanks

#include "mainwindow.h"

#include <QApplication>

/**
 * main
 */
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow win;

    win.show();
    return app.exec();
}

