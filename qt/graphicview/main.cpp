/**
 * main.cpp
 * 2022-06-01 K.OHWADA
 */

#include <QtWidgets/QApplication>
#include "MainWindow.h"


/**
 * main
 */
int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    MainWindow *mainWin = new MainWindow();

// a little bigger than the scene
    mainWin->setGeometry(10, 10, 340, 260);

    mainWin->setWindowTitle("GraphicView");

    mainWin->show();
        
    return app.exec();
}

