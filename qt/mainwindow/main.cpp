/**
 * main.cpp
 * 2022-06-01 K.OHWADA
 */

// http://qt-log.open-memo.net/sub/first__make_window.html

#include <QtWidgets/QApplication>
#include "MainWindow.h"


/**
 * main
 */
int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    MainWindow *mainWin = new MainWindow();
    mainWin->setGeometry(0, 10, 200, 300);
        //初期座標と大きさを設定
    mainWin->setWindowTitle("window");
        //ウインドウのタイトル
    mainWin->show();
        
    return app.exec();
}

