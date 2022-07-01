/**
 * main.cpp
 * 2022-06-01 K.OHWADA
 */

#include <QApplication>
#include "MainWindow.h"

/**
 * main
 */
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    MainWindow *win = new MainWindow();
   
    win->show();

    return a.exec();
}

