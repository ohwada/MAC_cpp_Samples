#pragma once

#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QScreen>
#include <QApplication>
#include <QKeyEvent>

//#include "game.h"

class GameMenu : public QWidget
{
    Q_OBJECT
public:
    explicit GameMenu(QWidget *parent = nullptr);

signals:
    void play();
    void newgame();
    void settings();
    void exit();
};

#endif // GAMEMENU_H
