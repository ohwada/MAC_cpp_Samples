// change log
// 2022-06-01 K.OHWADA
// #include <QAction>

/*
 * CMainWindow - modern Qt GUI class for PDA Maze game.
 *
 * Struction of menu:
 *     |
 *     +-Game
 *     |    |
 *     |    +-New Game <F5>
 *     |    |
 *     |    +-Quit <F10>
 *     |
 *     +-Settings
 *     |    |
 *     |    +-Timer
 *     |    |   |
 *     |    |   +-Timer Up
 *     |    |   |
 *     |    |   +-Timer Down
 *     |    |
 *     |    +-Map
 *     |    |   |
 *     |    |   +-All
 *     |    |   |
 *     |    |   +-Build
 *     |    |   |
 *     |    |   +-None
 *     |    |
 *     |    +-Size of map
 *     |    |   |
 *     |    |   +-9x9
 *     |    |   |
 *     |    |   +-19x19
 *     |    |   |
 *     |    |   +-29x29
 *     |    |   |
 *     |    |   +-39x39
 *     |    |   |
 *     |    |   +-49x49
 *     |    |
 *     |    +-Step Counter
 *     |    |
 *     |    +-Screen Size
 *     |    |   |
 *     |    |   +-160x177
 *     |    |   |
 *     |    |   +-240x265
 *     |    |   |
 *     |    |   +-480x531
 *     |    |
 *     |    +-Language
 *     |        |
 *     |        +-English
 *     |        |
 *     |        +-Spanish
 *     |        |
 *     |        +-Russian
 *     |
 *     +-Help
 *          |
 *          +-Control Keys <F1>
 *          |
 *          +-About PDA Maze
 *          |
 *          +-About Qt...
 *
 * Copyright (C) 2014 EXL <exlmotodev@gmail.com>
*/

#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#include "CIniConfig.h"
#include "CPlayField.h"

#include <QAction>

#include <QActionGroup>
#include <QMainWindow>
#include <QMenu>
#include <QTranslator>

class CMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    CMainWindow(QWidget *parent = 0);
    ~CMainWindow();

private:
    CIniConfig *m_IniConfig;
    CPlayField *m_PlayField;

    QTranslator m_AppTranslator;

    QAction *m_actionNewGame;
    QAction *m_actionQuit;
    QAction *m_actionShowStep;
    QAction *m_actionSmoothScreen;
    QAction *m_actionHelp;
    QAction *m_actionAbout;
    QAction *m_actionAboutQt;

    QAction *m_actionTimer;
    QActionGroup *m_actionGroupTimer;
    QAction *m_actionMapMode;
    QActionGroup *m_actionGroupMapMode;
    QAction *m_actionMapSize;
    QActionGroup *m_actionGroupMapSize;
    QAction *m_actionScaleScreen;
    QActionGroup *m_actionGroupScaleScreen;
    QAction *m_actionAppLang;
    QActionGroup *m_actionGroupAppLang;

    QMenu *m_menuFile;
    QMenu *m_menuSettings;
    QMenu *m_menuHelp;

    QMenu *m_menupTimer;
    QMenu *m_menupMapMode;
    QMenu *m_menupMapSize;
    QMenu *m_menupAppLang;
    QMenu *m_menupScaleScreen;

private:
    void createActions(void);
    void createMenus(void);
    QMenu *createTimerMenu(void);
    QMenu *createMapModeMenu(void);
    QMenu *createMapSizeMenu(void);
    QMenu *createScaleScreenMenu(void);
    QMenu *createLanguageMenu(void);
    void disableSmoothScreen(void);
    void loadTranslations(void);
    void retranslateUi(void);
    void detFixedSize(int aScreenScale);

private slots:
    void slotTimerModeChange(QAction *);
    void slotMapModeChange(QAction *);
    void slotMapSizeChange(QAction *);
    void slotScaleScreenChange(QAction *);
    void slotShowStepChange(bool aShowStep);
    void slotSmoothScreenChange(bool aSmoothScreen);
    void slotSwitchLanguage(QAction *);

protected:
    void closeEvent(QCloseEvent *event);
};

#endif // CMAINWINDOW_H
