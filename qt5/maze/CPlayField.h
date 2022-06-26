// change log
// 2022-06-01 K.OHWADA
// #include <QWidget>

/*
 * CPlayField - the PDA Maze widget.
 *
 * This file may be distributed and/or modified under the terms of the
 * GNU General Public License version 2 as published by the Free Software
 * Foundation and appearing in the file LICENSE.GPL included in the
 * packaging of this file.
 *
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See COPYING for GPL licensing information.
 *
 * Copyright (C) 2001 Bill Kendrick <bill@newbreedsoftware.com>
 * Copyright (C) 2002 Robert Ernst <robert.ernst@maxxio.com>
 * Copyright (C) 2014 EXL <exlmotodev@gmail.com>
 */

#ifndef CPLAYFIELD_H
#define CPLAYFIELD_H

#include "CIniConfig.h"

#include <QPainter>
#include <QPixmap>
#include <QTimer>

// #include <QWidget>
#include <QtWidgets/QWidget>

class CPlayField : public QWidget
{
    Q_OBJECT

public:
    CPlayField(QWidget *parent = 0);
    ~CPlayField();

private:
    enum TDistance {
        EDistanceFar,
        EDistanceMid,
        EDistanceClose,
    };

    enum TGameState {
        EIntro,
        EPlaying,
        EViewMap,
        EGameOverWin,
        EGameOverLoose,
        EHelp
    } e_GameState;

    enum TDirections {
        ENorth,
        EEast,
        ESouth,
        EWest,
    } e_Direction;

private:
    enum CIniConfig::TTimerModes e_TimerMode;
    enum CIniConfig::TMapModes e_MapMode;
    static const int KMaxMapSize = 49;
    int mapSize;

    int xPos;
    int yPos;
    int xPosInc[4];
    int yPosInc[4];

    int timerCounter;
    int stepCounter;
    bool showStep;
    int scaleScreen;
    bool smoothScreen;

    QString m_RtStringStep;
    QString m_RtStringCopyright;
    QString m_RtStringGameName;
    QString m_RtStringCtrlKeysTitle;
    QString m_RtStringCtrlKeysBody;
    QString m_AppLang;

    int theMaze[KMaxMapSize][KMaxMapSize];
    int viewedMaze[KMaxMapSize][KMaxMapSize];

private:
    QPixmap *m_MainPixmap;
    QTimer *m_GameTimer;

private: // Images
    QPixmap m_BackgroundEast;
    QPixmap m_BackgroundNorth;
    QPixmap m_BackgroundSouth;
    QPixmap m_BackgroundWest;

    QPixmap m_FarDistanceCenter;
    QPixmap m_FarDistanceCenterBright;
    QPixmap m_FarDistanceLeft;
    QPixmap m_FarDistanceLeftBright;
    QPixmap m_FarDistanceRight;
    QPixmap m_FarDistanceRightBright;

    QPixmap m_MiddleDistanceCenter;
    QPixmap m_MiddleDistanceCenterBright;
    QPixmap m_MiddleDistanceLeft;
    QPixmap m_MiddleDistanceLeftBright;
    QPixmap m_MiddleDistanceRight;
    QPixmap m_MiddleDistanceRightBright;

    QPixmap m_CloseDistanceCenter;
    QPixmap m_CloseDistanceCenterBright;
    QPixmap m_CloseDistanceLeft;
    QPixmap m_CloseDistanceLeftBright;
    QPixmap m_CloseDistanceRight;
    QPixmap m_CloseDistanceRightBright;

    QPixmap m_CompassEast;
    QPixmap m_ComapassNorth;
    QPixmap m_CompassSouth;
    QPixmap m_CompassWest;

    QPixmap m_PicTimeUp;
    QPixmap m_PicGameTitle;
    QPixmap m_PicYouWin;

    QPixmap m_Ground;
    QPixmap m_TimerNumbers;

private:
    void drawIntro(void);
    void drawHelp(void);
    void drawPlaying(void);
    void drawViewMap(void);
    void drawGameOverWin(void);
    void drawGameOverLoose(void);
    void drawAllOnWidget(QPainter &painter);

    void moveForward(void);
    void moveBackward(void);
    void turnLeft(void);
    void turnRight(void);

    void makeMaze(void);
    int mazeChunk(int aXPos, int aYPos);

    void drawMazeView(QPainter &painter);
    void drawCompass(QPainter &painter);
    void drawTime(QPainter &painter);
    void drawStepCounter(QPainter &painter);
    void drawWall(QPainter &painter, int aBlock,
                  enum TDistance aDist, int aXOffset);
    void drawFarCenter(QPainter &painter, int aX);
    void drawFarLeft(QPainter &painter, int aX);
    void drawFarRight(QPainter &painter, int aX);
    void drawMidCenter(QPainter &painter, int aX);
    void drawMidLeft(QPainter &painter, int aX);
    void drawMidRight(QPainter &painter, int aX);
    void drawCloseCenter(QPainter &painter);
    void drawCloseLeft(QPainter &painter);
    void drawCloseRight(QPainter &painter);

protected:
    void paintEvent(QPaintEvent *event);
    void showEvent(QShowEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);

public slots:
    void timerTick(void);
    void startGame(void);
    void stopGame(void);
    void showHelp(void);

public:
    void setTimerMode(int aTimerMode);
    void setMapMode(int aMapMode);
    void setMapSize(int aMapSize);
    void setStepStatus(bool aShowStep);
    void setScaleScreen(int aScaleScreen);
    void setSmoothScreen(bool aSmoothScreen);
    void setAppLang(QString aAppLang);
    void retranslateUi(void);
};

#endif // CPLAYFIELD_H
