#pragma once
/**
 * MainWindpw.h
 * 2022-06-01 K.OHWADA
 */

// http://qt-log.open-memo.net/sub/first__make_window.html

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QKeyEvent>

/**
 * class MainWindow
 */
class MainWindow : public QMainWindow
{
public:
    MainWindow();

protected:
    void keyPressEvent(QKeyEvent *pEvent);

};

#endif
