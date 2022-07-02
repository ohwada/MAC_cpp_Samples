#pragma once
/**
 * map_creator.h
 * 2022-06-01 K.OHWADA
 */

// original : https://github.com/magziim/Tanks

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QVBoxLayout>

#include "game.h"
#include "menu.h"
#include "gamemenu.h"


/**
 * class MainWindow
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:

    Game* game_window;

private slots:
    void Play();
    void Settings();
    void Exit();
   void slotGameOver(int ID);

    void openMenu();
    void closeMenu();
    void NewGame();
};


#endif // MAINWINDOW_H
