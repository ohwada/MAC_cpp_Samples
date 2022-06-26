// change log
// 2022-06-01 K.OHWADA
// warning: 'width' is deprecated


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

#include "CPlayField.h"

#include <QApplication>
#include <QDebug>
#include <QFont>
#include <QFontMetrics>
#include <QResizeEvent>

#ifndef APP_VERSION
#define APP_VERSION "0.1"
#endif

CPlayField::CPlayField(QWidget *parent) :
    QWidget(parent)
{
    /* Setup the default values for some member variables */
    e_TimerMode = CIniConfig::ETimerUp;
    e_MapMode = CIniConfig::EMapBuild;
    e_Direction = ENorth;
    e_GameState = EIntro;
    mapSize = CIniConfig::EMapSize9x9;
    xPos = -1;
    yPos = -1;
    m_MainPixmap = NULL;
    timerCounter = 0;

    stepCounter = 0;
    showStep = false;

    m_GameTimer = new QTimer(this);
    connect(m_GameTimer, SIGNAL(timeout()), this, SLOT(timerTick()));

    /* Initialize the xpos/ypos increment counter */
    xPosInc[ENorth] = 0;
    xPosInc[EEast] = 1;
    xPosInc[ESouth] = 0;
    xPosInc[EWest] = -1;
    yPosInc[ENorth] = -1;
    yPosInc[EEast] = 0;
    yPosInc[ESouth] = 1;
    yPosInc[EWest] = 0;

    m_MainPixmap = new QPixmap(160, 177);

    /* Load XMP and PNG untranslatable images */
    m_BackgroundEast.load("://images/bkg_east.xpm");
    m_BackgroundNorth.load("://images/bkg_north.xpm");
    m_BackgroundSouth.load("://images/bkg_south.xpm");
    m_BackgroundWest.load("://images/bkg_west.xpm");

    m_FarDistanceCenter.load("://images/far_center.xpm");
    m_FarDistanceCenterBright.load("://images/far_center_bright.xpm");
    m_FarDistanceLeft.load("://images/far_left.xpm");
    m_FarDistanceLeftBright.load("://images/far_left_bright.xpm");
    m_FarDistanceRight.load("://images/far_right.xpm");
    m_FarDistanceRightBright.load("://images/far_right_bright.xpm");

    m_MiddleDistanceCenter.load("://images/middle_center.xpm");
    m_MiddleDistanceCenterBright.load("://images/middle_center_bright.xpm");
    m_MiddleDistanceLeft.load("://images/middle_left.xpm");
    m_MiddleDistanceLeftBright.load("://images/middle_left_bright.xpm");
    m_MiddleDistanceRight.load("://images/middle_right.xpm");
    m_MiddleDistanceRightBright.load("://images/middle_right_bright.xpm");

    m_CloseDistanceCenter.load("://images/close_center.xpm");
    m_CloseDistanceCenterBright.load("://images/close_center_bright.xpm");
    m_CloseDistanceLeft.load("://images/close_left.xpm");
    m_CloseDistanceLeftBright.load("://images/close_left_bright.xpm");
    m_CloseDistanceRight.load("://images/close_right.xpm");
    m_CloseDistanceRightBright.load("://images/close_right_bright.xpm");

    m_Ground.load("://images/ground.xpm");

    m_TimerNumbers.load("://images/numbers.xpm");
    m_PicGameTitle.load("://images/title.png");
}

void CPlayField::retranslateUi(void)
{
    m_RtStringStep = tr("Step: %1");
    m_RtStringCopyright = tr("Original game by Bill Kendrick\n"
                             "Zaurus port by Robert Ernst\n"
                             "Qt port by EXL\n"
                             "Version: %1, (c) 2001-2014").arg(APP_VERSION);
    m_RtStringGameName = tr("PDA\nMaze");
    m_RtStringCtrlKeysTitle = tr("Control\nKeys");
    m_RtStringCtrlKeysBody = tr("Move: D-pad or W, A, S, D\n"
                                "Show Map: Space or Enter\n"
                                "New Game: F5\n"
                                "Exit: Esc and F10");

    /* Load PNG translatable images */
    m_CompassEast.load(QString("://images/images_i18n/cmp_east_%1.png")
                       .arg(m_AppLang));
    m_ComapassNorth.load(QString("://images/images_i18n/cmp_north_%1.png")
                         .arg(m_AppLang));
    m_CompassSouth.load(QString("://images/images_i18n/cmp_south_%1.png")
                        .arg(m_AppLang));
    m_CompassWest.load(QString("://images/images_i18n/cmp_west_%1.png")
                       .arg(m_AppLang));

    m_PicTimeUp.load(QString("://images/images_i18n/timeup_%1.png")
                     .arg(m_AppLang));
    m_PicYouWin.load(QString("://images/images_i18n/youwin_%1.png")
                     .arg(m_AppLang));

    qDebug() << "Retranslate PlayerField, Lang: " << m_AppLang;

    repaint();
}

void CPlayField::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    switch (e_GameState) {
    case EIntro:
        drawIntro();
        break;
    case EPlaying:
        drawPlaying();
        break;
    case EViewMap:
        drawViewMap();
        break;
    case EGameOverWin:
        drawGameOverWin();
        break;
    case EGameOverLoose:
        drawGameOverLoose();
        break;
    case EHelp:
        drawHelp();
        break;
    }
}

void CPlayField::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    setFocusPolicy(Qt::StrongFocus);
}

void CPlayField::keyPressEvent(QKeyEvent *event)
{
    QWidget::keyPressEvent(event);
    switch (event->key()) {
    case Qt::Key_Up:
    case Qt::Key_W:
    {
        if (e_GameState == EPlaying) {
            moveForward();
        }
        break;
    }
    case Qt::Key_Down:
    case Qt::Key_S:
    {
        if (e_GameState == EPlaying) {
            moveBackward();
        }
        break;
    }
    case Qt::Key_Left:
    case Qt::Key_A:
    {
        if (e_GameState == EPlaying) {
            turnLeft();
        }
        break;
    }
    case Qt::Key_Right:
    case Qt::Key_D:
    {
        if (e_GameState == EPlaying) {
            turnRight();
        }
        break;
    }
    case Qt::Key_Space:
    case Qt::Key_Enter:
    case Qt::Key_Return:
    {
        if (e_GameState == EPlaying) {
            e_GameState = EViewMap;
            repaint();
        } else if (e_GameState == EViewMap) {
            e_GameState = EPlaying;
            repaint();
        } else {
            startGame();
        }
        break;
    }
    case Qt::Key_Escape:
    {
        if (e_GameState == EPlaying || e_GameState == EViewMap) {
            stopGame();
        }
        break;
    }
    }
}

void CPlayField::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
    if (e_GameState == EPlaying) {
        int xMax = width();
        if (event->y() > xMax) {
            /* Click on the lower area of the screen: compass, maze, timer */
            e_GameState = EViewMap;
            repaint();
        } else if (abs(event->x() - event->y()) > 10
                   && abs(xMax - event->x() - event->y()) > 10) {
            /* Click in the upper/lower/left/right quarter of the screen */
            int x = event->x();
            int y = event->y();
            if (x > y) {
                if ((xMax - x) > y) {
                    moveForward();
                } else {
                    turnRight();
                }
            } else {
                if ((xMax - y) < x) {
                    moveBackward();
                } else {
                    turnLeft();
                }
            }
        }
    } else if (e_GameState == EViewMap) {
        e_GameState = EPlaying;
        repaint();
    } else {
        startGame();
    }
}

void CPlayField::timerTick(void)
{
    if (e_TimerMode == CIniConfig::ETimerDown) {
        if (timerCounter > 0) {
            timerCounter--;
            if (timerCounter == 0) {
                e_GameState = EGameOverLoose;
                m_GameTimer->stop();
            }
        }
    } else {
        timerCounter++;
    }
    repaint();
}

void CPlayField::startGame(void)
{
    e_GameState = EPlaying;
    m_GameTimer->start(1000);

    if (e_TimerMode == CIniConfig::ETimerDown) {
        timerCounter = (mapSize * mapSize ) - 1;
    } else {
        timerCounter = 0;
    }

    stepCounter = 0;
    makeMaze();
    repaint();
}

void CPlayField::stopGame(void)
{
    stepCounter = 0;
    if (e_GameState != EIntro) {
        e_GameState = EIntro;
        m_GameTimer->stop();
        repaint();
    }
}

void CPlayField::showHelp(void)
{
    stepCounter = 0;
    if (e_GameState != EHelp) {
        e_GameState = EHelp;
        m_GameTimer->stop();
        repaint();
    }
}

void CPlayField::setTimerMode(int aTimerMode)
{
    if (aTimerMode != e_TimerMode) {
        switch (aTimerMode) {
        case CIniConfig::ETimerDown:
            e_TimerMode = CIniConfig::ETimerDown;
            break;
        default:
            e_TimerMode = CIniConfig::ETimerUp;
            break;
        }
        if (e_GameState == EPlaying || e_GameState == EViewMap) {
            startGame();
        }
    }
}

void CPlayField::setMapMode(int aMapMode)
{
    if (aMapMode != e_MapMode) {
        switch (aMapMode) {
        case CIniConfig::EMapAll:
            e_MapMode = CIniConfig::EMapAll;
            break;
        case CIniConfig::EMapNone:
            e_MapMode = CIniConfig::EMapNone;
            break;
        default:
            e_MapMode = CIniConfig::EMapBuild;
            break;
        }
        if (e_GameState == EPlaying || e_GameState == EViewMap) {
            startGame();
        }
    }
}

void CPlayField::setMapSize(int aMapSize)
{
    if (aMapSize != mapSize) {
        mapSize = aMapSize;
        if (e_GameState == EPlaying || e_GameState == EViewMap) {
            startGame();
        }
    }
}

void CPlayField::setStepStatus(bool aShowStep)
{
    showStep = aShowStep;
    repaint();
}

void CPlayField::setScaleScreen(int aScaleScreen)
{
    if (!aScaleScreen) {
        smoothScreen = false;
    }
    scaleScreen = aScaleScreen;
    repaint();
}

void CPlayField::setSmoothScreen(bool aSmoothScreen)
{
    if (!scaleScreen) {
        smoothScreen = false;
    } else {
        smoothScreen = aSmoothScreen;
    }
    repaint();
}

void CPlayField::setAppLang(QString aAppLang)
{
    m_AppLang = aAppLang;
}

void CPlayField::drawIntro(void)
{
    QPainter m_PainterPixmap(m_MainPixmap);
    QPainter m_PainterWidget(this);
    QColor m_ColorBlack(0, 0, 0);
    QColor m_ColorWhite(255, 255, 255);
    QColor m_ColorDirtyWhite(242, 243, 244);

    int xMax = 160;
    int yMax = 177;

    m_PainterPixmap.fillRect(0, 0, xMax, yMax, m_ColorWhite);
    m_PainterPixmap.setPen(m_ColorWhite);

    QFont m_FontBig = m_PainterPixmap.font();
    m_FontBig.setPixelSize(30);
    m_FontBig.setBold(true);
    QFont m_FontSmall = m_PainterPixmap.font();
    m_FontSmall.setPixelSize(10);
    m_PainterPixmap.drawPixmap(0, 0, m_PicGameTitle);
    m_PainterPixmap.setFont(m_FontBig);
    m_PainterPixmap.setPen(m_ColorBlack);
    m_PainterPixmap.drawText(5, 5, xMax, xMax / 2,
                             Qt::AlignHCenter | Qt::AlignVCenter,
                             m_RtStringGameName);
    m_PainterPixmap.setPen(m_ColorWhite);
    m_PainterPixmap.drawText(0, 0, xMax, xMax / 2,
                             Qt::AlignHCenter | Qt::AlignVCenter,
                             m_RtStringGameName);

    m_PainterPixmap.fillRect(3, (yMax / 2) + 25, xMax - (3 * 2), 50,
                             m_ColorDirtyWhite);

    m_PainterPixmap.setFont(m_FontSmall);
    m_PainterPixmap.setPen(m_ColorBlack);
    m_PainterPixmap.drawText(4, (yMax / 2) + 25, xMax - (4 * 2), 50,
                             Qt::AlignHCenter | Qt::AlignVCenter,
                             m_RtStringCopyright);
    drawAllOnWidget(m_PainterWidget);
}

void CPlayField::drawHelp(void)
{
    QPainter m_PainterPixmap(m_MainPixmap);
    QPainter m_PainterWidget(this);
    QColor m_ColorBlack(0, 0, 0);
    QColor m_ColorWhite(255, 255, 255);
    QColor m_ColorDirtyWhite(250, 240, 190);

    int xMax = 160;
    int yMax = 177;

    m_PainterPixmap.fillRect(0, 0, xMax, yMax, m_ColorWhite);
    m_PainterPixmap.setPen(m_ColorWhite);

    QFont m_FontBig = m_PainterPixmap.font();
    m_FontBig.setPixelSize(30);
    m_FontBig.setBold(true);
    QFont m_FontSmall = m_PainterPixmap.font();
    m_FontSmall.setPixelSize(10);
    m_PainterPixmap.drawPixmap(0, 0, m_PicGameTitle);
    m_PainterPixmap.setFont(m_FontBig);
    m_PainterPixmap.setPen(m_ColorBlack);
    m_PainterPixmap.drawText(5, 5, xMax, xMax / 2,
                             Qt::AlignHCenter | Qt::AlignVCenter,
                             m_RtStringCtrlKeysTitle);
    m_PainterPixmap.setPen(m_ColorWhite);
    m_PainterPixmap.drawText(0, 0, xMax, xMax / 2,
                             Qt::AlignHCenter | Qt::AlignVCenter,
                             m_RtStringCtrlKeysTitle);

    m_PainterPixmap.fillRect(3, (yMax / 2) + 25, xMax - (3 * 2), 50,
                             m_ColorDirtyWhite);

    m_PainterPixmap.setFont(m_FontSmall);
    m_PainterPixmap.setPen(m_ColorBlack);
    m_PainterPixmap.drawText(5, (yMax / 2) + 25, xMax - (4 * 2), 50,
                             Qt::AlignLeft,
                             m_RtStringCtrlKeysBody);
    drawAllOnWidget(m_PainterWidget);
}

void CPlayField::drawPlaying(void)
{
    QPainter m_PainterPixmap(m_MainPixmap);
    QPainter m_PainterWidget(this);
    QColor m_ColorWhite(255, 255, 255);

    int xMax = 160;
    int yMax = 177;

    m_PainterPixmap.fillRect(0, 0, xMax, yMax, m_ColorWhite);
    m_PainterPixmap.setPen(m_ColorWhite);

    drawMazeView(m_PainterPixmap);
    drawCompass(m_PainterPixmap);
    drawTime(m_PainterPixmap);
    drawStepCounter(m_PainterPixmap);
    drawAllOnWidget(m_PainterWidget);
}

void CPlayField::drawViewMap(void)
{
    QPainter m_PainterPixmap(m_MainPixmap);
    QPainter m_PainterWidget(this);
    QColor m_colorBlack(0, 0, 0);
    QColor m_colorGrey(192, 192, 192);
    QColor m_colorWhite(255, 255, 255);
    QColor m_colorRed(255, 0, 0);

    int xMax = 160;
    int yMax = 177;

    int xSize = xMax / mapSize;
    int ySize = xMax / mapSize;
    int xOffs = (xMax - xSize * mapSize) / 2;
    int yOffs = (xMax - ySize * mapSize) / 2;

    m_PainterPixmap.fillRect(0, 0, xMax, yMax, m_colorWhite);
    m_PainterPixmap.setPen(m_colorWhite);

    for (int y = 0; y < mapSize; y++) {
        for (int x = 0; x < mapSize; x++) {
            if (x == xPos && y == yPos) {
                m_PainterPixmap.fillRect(xOffs + x * xSize,
                                         yOffs + y * ySize,
                                         xSize, ySize, m_colorRed);
            } else if (e_MapMode == CIniConfig::EMapNone
                       || (e_MapMode == CIniConfig::EMapBuild
                           && viewedMaze[y][x] == false)) {
                m_PainterPixmap.fillRect(xOffs + x * xSize,
                                         yOffs + y * ySize,
                                         xSize, ySize, m_colorGrey);
            } else if (theMaze[y][x] == 255) {
                m_PainterPixmap.fillRect(xOffs + x * xSize,
                                         yOffs + y * ySize,
                                         xSize, ySize, m_colorBlack);
            } else {
                m_PainterPixmap.fillRect(xOffs + x * xSize,
                                         yOffs + y * ySize,
                                         xSize, ySize, m_colorWhite);
            }
        }
    }

    drawCompass(m_PainterPixmap);
    drawTime(m_PainterPixmap);
    drawAllOnWidget(m_PainterWidget);
}

void CPlayField::drawGameOverWin(void)
{
    QPainter m_PainterPixmap(m_MainPixmap);
    QPainter m_PainterWidget(this);
    QColor m_ColorWhite(255, 255, 255);

    int xMax = 160;
    int yMax = 177;

    m_PainterPixmap.fillRect(0, 0, xMax, yMax, m_ColorWhite);
    m_PainterPixmap.setPen(m_ColorWhite);

    int xOffs = (xMax - m_PicYouWin.width()) / 2;
    int yOffs = (yMax - m_PicYouWin.height()) / 2;

    drawMazeView(m_PainterPixmap);
    drawCompass(m_PainterPixmap);
    drawTime(m_PainterPixmap);
    drawStepCounter(m_PainterPixmap);

    m_PainterPixmap.drawPixmap(xOffs, yOffs, m_PicYouWin);

    drawAllOnWidget(m_PainterWidget);
}

void CPlayField::drawGameOverLoose(void)
{
    QPainter m_PainterPixmap(m_MainPixmap);
    QPainter m_PainterWidget(this);
    QColor m_ColorWhite(255, 255, 255);

    int xMax = 160;
    int yMax = 177;

    m_PainterPixmap.fillRect(0, 0, xMax, yMax, m_ColorWhite);
    m_PainterPixmap.setPen(m_ColorWhite);

    int xOffs = (xMax - m_PicTimeUp.width()) / 2;
    int yOffs = (yMax - m_PicTimeUp.height()) / 2;

    drawMazeView(m_PainterPixmap);
    drawCompass(m_PainterPixmap);
    drawTime(m_PainterPixmap);
    drawStepCounter(m_PainterPixmap);

    m_PainterPixmap.drawPixmap(xOffs, yOffs, m_PicTimeUp);

    drawAllOnWidget(m_PainterWidget);
}

void CPlayField::drawAllOnWidget(QPainter &painter)
{
    switch (scaleScreen) {
    case CIniConfig::ERes160x177:
    default:
        painter.drawPixmap(0, 0, *m_MainPixmap);
        break;
    case CIniConfig::ERes240x265:
        painter.drawPixmap(0, 0,
                           m_MainPixmap->scaled(240, 265,
                                                Qt::IgnoreAspectRatio,
                                                (smoothScreen) ?
                                                    Qt::SmoothTransformation:
                                                    Qt::FastTransformation));
        break;
    case CIniConfig::ERes480x531:
        painter.drawPixmap(0, 0,
                           m_MainPixmap->scaled(480, 531,
                                                Qt::IgnoreAspectRatio,
                                                (smoothScreen) ?
                                                    Qt::SmoothTransformation:
                                                    Qt::FastTransformation));
        break;
    }
}

void CPlayField::moveForward(void)
{
    int _xPos = xPos + xPosInc[e_Direction];
    int _yPos = yPos + yPosInc[e_Direction];

    if (theMaze[_yPos][_xPos] != 255) {
        stepCounter++;
        xPos = _xPos;
        yPos = _yPos;
        viewedMaze[yPos - 1][xPos - 1] = true;
        viewedMaze[yPos - 1][xPos + 0] = true;
        viewedMaze[yPos - 1][xPos + 1] = true;
        viewedMaze[yPos + 0][xPos - 1] = true;
        viewedMaze[yPos + 0][xPos + 0] = true;
        viewedMaze[yPos + 0][xPos + 1] = true;
        viewedMaze[yPos + 1][xPos - 1] = true;
        viewedMaze[yPos + 1][xPos + 0] = true;
        viewedMaze[yPos + 1][xPos + 1] = true;
        if (xPos == 1 && yPos == 2) {
            e_GameState = EGameOverWin;
            m_GameTimer->stop();
        }
        repaint();
    }
}

void CPlayField::moveBackward(void)
{
    int _xPos = xPos - xPosInc[e_Direction];
    int _yPos = yPos - yPosInc[e_Direction];

    if (theMaze[_yPos][_xPos] != 255) {
        stepCounter++;
        xPos = _xPos;
        yPos = _yPos;
        viewedMaze[yPos - 1][xPos - 1] = true;
        viewedMaze[yPos - 1][xPos + 0] = true;
        viewedMaze[yPos - 1][xPos + 1] = true;
        viewedMaze[yPos + 0][xPos - 1] = true;
        viewedMaze[yPos + 0][xPos + 0] = true;
        viewedMaze[yPos + 0][xPos + 1] = true;
        viewedMaze[yPos + 1][xPos - 1] = true;
        viewedMaze[yPos + 1][xPos + 0] = true;
        viewedMaze[yPos + 1][xPos + 1] = true;
        if (xPos == 1 && yPos == 2) {
            e_GameState = EGameOverWin;
        }
        repaint();
    }
}

void CPlayField::turnLeft(void)
{
    switch (e_Direction) {
    case ENorth:
        e_Direction = EWest;
        break;
    case EEast:
        e_Direction = ENorth;
        break;
    case ESouth:
        e_Direction = EEast;
        break;
    case EWest:
        e_Direction = ESouth;
        break;
    }
    repaint();
}

void CPlayField::turnRight(void)
{
    switch (e_Direction) {
    case ENorth:
        e_Direction = EEast;
        break;
    case EEast:
        e_Direction = ESouth;
        break;
    case ESouth:
        e_Direction = EWest;
        break;
    case EWest:
        e_Direction = ENorth;
        break;
    }
    repaint();
}

int CPlayField::mazeChunk(int aXPos, int aYPos)
{
    /* This is the function mazechunk() from Bill Kendricks pdamaze.c */
    return (aXPos > 0
            && aYPos > 0
            && aXPos < (mapSize - 1)
            && aYPos < (mapSize - 1)) ? theMaze[aYPos][aXPos] : -1;
}

void CPlayField::makeMaze(void)
{
    /* This is the function create_maze() from Bill Kendricks pdamaze.c */
    int x;
    int y;

    for (y = 1; y < (mapSize - 1); y++) {
        for (x = 1; x < (mapSize - 1); x++) {
            theMaze[y][x] = 255;
        }
        theMaze[y][0] = -1;
        theMaze[y][mapSize - 1] = -1;
    }
    for (x = 0; x < mapSize; x++) {
        theMaze[0][x] = -1;
        theMaze[mapSize - 1][x] = -1;
    }

    y = 2;
    x = 2;
    int xx = 0;
    int j = 0;
    int ok = 2;
    theMaze[y][x] = 5;

    do {
        if (ok == 2) {
            j = (rand() % 4);
            xx = j;
        }
        ok = 0;
        int nx = x + xPosInc[j] * 2;
        int ny = y + yPosInc[j] * 2;
        if (mazeChunk(nx, ny) == 255) {
            theMaze[ny][nx] = j + 1;
            theMaze[y + yPosInc[j]][x + xPosInc[j]] = 0;
            x = nx;
            y = ny;
            ok = 2;
        }
        if (ok == 0) {
            if (j < 3) {
                j = j + 1;
                while (j > 3) {
                    j = j - 4;
                }
            } else {
                j = 0;
            }
            if (j != xx) {
                ok = 1;
            }
        }
        if (ok == 0) {
            j = mazeChunk(x, y);
            theMaze[y][x] = 0;
            if (j < 5) {
                x = x - (xPosInc[j - 1] * 2);
                y = y - (yPosInc[j - 1] * 2);
                ok = 2;
            }
        }
    } while (ok != 0);

    for (x = 0; x < mapSize; x++) {
        viewedMaze[0][x] = 1;
        viewedMaze[1][x] = 1;
        viewedMaze[mapSize - 2][x] = 1;
        viewedMaze[mapSize - 1][x] = 1;
    }
    for (y = 2; y < mapSize - 2; y++) {
        viewedMaze[y][0] = 1;
        viewedMaze[y][1] = 1;
        viewedMaze[y][mapSize - 2] = 1;
        viewedMaze[y][mapSize - 1] = 1;
        for (x = 2; x < mapSize - 2; x++) {
            viewedMaze[y][x] = 0;
        }
    }

    theMaze[2][1] = 0;

    xPos = mapSize / 2 + 1;
    yPos = mapSize / 2 + 1;
    xPos = xPos + (xPos % 2);
    yPos = yPos + (yPos % 2);
    do {
        switch (rand() % 4) {
        case 0:
            e_Direction = ENorth;
            break;
        case 1:
            e_Direction = ESouth;
            break;
        case 2:
            e_Direction = EWest;
            break;
        case 3:
            e_Direction = EEast;
            break;
        }
    } while (theMaze[yPos + yPosInc[e_Direction]][xPos + xPosInc[e_Direction]]
             == 255);
}

void CPlayField::drawMazeView(QPainter &painter)
{
    switch (e_Direction) {
    case ENorth:
        painter.drawPixmap(0, 0, m_BackgroundNorth);
        break;
    case EEast:
        painter.drawPixmap(0, 0, m_BackgroundEast);
        break;
    case ESouth:
        painter.drawPixmap(0, 0, m_BackgroundSouth);
        break;
    case EWest:
        painter.drawPixmap(0, 0, m_BackgroundWest);
        break;
    }
    painter.drawPixmap(0, 80, m_Ground);

    switch (e_Direction) {
    case ENorth:
        drawWall(painter, mazeChunk(xPos - 1, yPos - 3), EDistanceFar, -1);
        drawWall(painter, mazeChunk(xPos + 1, yPos - 3), EDistanceFar, 1);
        drawWall(painter, mazeChunk(xPos + 0, yPos - 3), EDistanceFar, 0);
        drawWall(painter, mazeChunk(xPos - 1, yPos - 2), EDistanceMid, -1);
        drawWall(painter, mazeChunk(xPos + 1, yPos - 2), EDistanceMid, 1);
        drawWall(painter, mazeChunk(xPos + 0, yPos - 2), EDistanceMid, 0);
        drawWall(painter, mazeChunk(xPos - 1, yPos - 1), EDistanceClose, -1);
        drawWall(painter, mazeChunk(xPos + 1, yPos - 1), EDistanceClose, 1);
        drawWall(painter, mazeChunk(xPos + 0, yPos - 1), EDistanceClose, 0);
        break;
    case EEast:
        drawWall(painter, mazeChunk(xPos + 3, yPos - 1), EDistanceFar, -1);
        drawWall(painter, mazeChunk(xPos + 3, yPos + 1), EDistanceFar, 1);
        drawWall(painter, mazeChunk(xPos + 3, yPos + 0), EDistanceFar, 0);
        drawWall(painter, mazeChunk(xPos + 2, yPos - 1), EDistanceMid, -1);
        drawWall(painter, mazeChunk(xPos + 2, yPos + 1), EDistanceMid, 1);
        drawWall(painter, mazeChunk(xPos + 2, yPos + 0), EDistanceMid, 0);
        drawWall(painter, mazeChunk(xPos + 1, yPos - 1), EDistanceClose, -1);
        drawWall(painter, mazeChunk(xPos + 1, yPos + 1), EDistanceClose, 1);
        drawWall(painter, mazeChunk(xPos + 1, yPos + 0), EDistanceClose, 0);
        break;
    case ESouth:
        drawWall(painter, mazeChunk(xPos + 1, yPos + 3), EDistanceFar, -1);
        drawWall(painter, mazeChunk(xPos - 1, yPos + 3), EDistanceFar, 1);
        drawWall(painter, mazeChunk(xPos + 0, yPos + 3), EDistanceFar, 0);
        drawWall(painter, mazeChunk(xPos + 1, yPos + 2), EDistanceMid, -1);
        drawWall(painter, mazeChunk(xPos - 1, yPos + 2), EDistanceMid, 1);
        drawWall(painter, mazeChunk(xPos + 0, yPos + 2), EDistanceMid, 0);
        drawWall(painter, mazeChunk(xPos + 1, yPos + 1), EDistanceClose, -1);
        drawWall(painter, mazeChunk(xPos - 1, yPos + 1), EDistanceClose, 1);
        drawWall(painter, mazeChunk(xPos + 0, yPos + 1), EDistanceClose, 0);
        break;
    case EWest:
        drawWall(painter, mazeChunk(xPos - 3, yPos + 1), EDistanceFar, -1);
        drawWall(painter, mazeChunk(xPos - 3, yPos - 1), EDistanceFar, 1);
        drawWall(painter, mazeChunk(xPos - 3, yPos + 0), EDistanceFar, 0);
        drawWall(painter, mazeChunk(xPos - 2, yPos + 1), EDistanceMid, -1);
        drawWall(painter, mazeChunk(xPos - 2, yPos - 1), EDistanceMid, 1);
        drawWall(painter, mazeChunk(xPos - 2, yPos + 0), EDistanceMid, 0);
        drawWall(painter, mazeChunk(xPos - 1, yPos + 1), EDistanceClose, -1);
        drawWall(painter, mazeChunk(xPos - 1, yPos - 1), EDistanceClose, 1);
        drawWall(painter, mazeChunk(xPos - 1, yPos + 0), EDistanceClose, 0);
        break;
    }
}

void CPlayField::drawCompass(QPainter &painter)
{
    int xMax = 160;

    switch (e_Direction) {
    case ENorth:
        painter.drawPixmap(0, xMax, m_ComapassNorth);
        break;
    case EEast:
        painter.drawPixmap(0, xMax, m_CompassEast);
        break;
    case ESouth:
        painter.drawPixmap(0, xMax, m_CompassSouth);
        break;
    case EWest:
        painter.drawPixmap(0, xMax, m_CompassWest);
        break;
    }
}

void CPlayField::drawTime(QPainter &painter)
{
    int xMax = 160;

    int min = (timerCounter / 60) % 60;
    int sec = timerCounter % 60;

    char time_string[5] = {
        (char)((min / 10) + '0'),
        (char)((min % 10) + '0'),
        ':',
        (char)((sec / 10) + '0'),
        (char)((sec % 10) + '0')
    };

    for (int i = 0; i < 5; i++) {
        int number = time_string[i] - '0';
        painter.drawPixmap(118 + i * 8, xMax + 2,
                           m_TimerNumbers, number * 8, 0, 8, 12);
    }
}

void CPlayField::drawStepCounter(QPainter &painter)
{
    if (showStep) {

// warning: 'width' is deprecated
    // int width = painter.fontMetrics().width(m_RtStringStep.arg(stepCounter));
        int width = painter.fontMetrics().horizontalAdvance( m_RtStringStep.arg(stepCounter) );

        int height = painter.fontMetrics().height();

        painter.fillRect(100, 2, width, height, QColor(242, 243, 244));

        painter.setPen(Qt::black);
        painter.drawText(100, 2, width, height,
                         Qt::AlignRight, m_RtStringStep.arg(stepCounter));
    }
}

void CPlayField::drawWall(QPainter &painter,
                          int aBlock, enum TDistance aDist, int aXOffset)
{
    if (aBlock == 255) {
        if (aDist == EDistanceFar) {
            if (aXOffset < 0) {
                drawFarCenter(painter, 80 - 12 + (aXOffset * 24));
                drawFarLeft(painter, 80 - 12 + (aXOffset * 24) + 24);
            } else if (aXOffset == 0) {
                drawFarCenter(painter, 80 - 12);
            } else if (aXOffset > 0) {
                drawFarCenter(painter, 80 - 12 + (aXOffset * 24));
                drawFarRight(painter, 80 - 12 + (aXOffset * 24) - 10);
            }
        } else if (aDist == EDistanceMid) {
            if (aXOffset < 0) {
                drawMidCenter(painter, 80 - 33 - (66 - 24)
                              + (aXOffset * 24));
                drawMidLeft(painter, 80 - 33 - (66 - 24)
                            + (aXOffset * 24) + 66);
            } else if (aXOffset == 0) {
                drawMidCenter(painter, 80 - 33);
            } else if (aXOffset > 0) {
                drawMidCenter(painter, 80 - 33 + (66 - 24)
                              + (aXOffset * 24));
                drawMidRight(painter, 80 - 33 + (66 - 24)
                             + (aXOffset * 24) - 21);
            }
        } else if (aDist == EDistanceClose) {
            if (aXOffset < 0) {
                drawCloseLeft(painter);
            } else if (aXOffset == 0) {
                drawCloseCenter(painter);
            } else if (aXOffset > 0) {
                drawCloseRight(painter);
            }
        }
    }
}

void CPlayField::drawFarCenter(QPainter &painter, int aX)
{
    painter.drawPixmap(aX, 80 - 12 + 1,
                       (e_Direction == ENorth || e_Direction == EWest)
                       ? m_FarDistanceCenterBright : m_FarDistanceCenter);
}

void CPlayField::drawFarLeft(QPainter &painter, int aX)
{
    QPixmap m_Pixmap;

    m_Pixmap = (e_Direction == ENorth || e_Direction == EEast)
            ? m_FarDistanceLeftBright : m_FarDistanceLeft;
    for (int y = 0; y < 11; y++) {
        if (!y) {
            continue;
        }
        painter.drawPixmap(aX, 80 - 12 + y, m_Pixmap, 0, y, y, 1);
        painter.drawPixmap(aX, 80 - 12 + 24 - y, m_Pixmap, 0, 23 - y, y, 1);
    }
    painter.drawPixmap(aX, 80 - 12 + 11, m_Pixmap, 0, 11, 12, 3);
}

void CPlayField::drawFarRight(QPainter &painter, int aX)
{
    QPixmap m_Pixmap;

    m_Pixmap = (e_Direction == ESouth || e_Direction == EWest)
            ? m_FarDistanceRightBright : m_FarDistanceRight;
    for (int y = 0; y < 11; y++) {
        painter.drawPixmap(aX + 11 - y, 80 - 12 + y, m_Pixmap, 11 - y, y, y, 1);
        painter.drawPixmap(aX + 11 - y, 80 - 12 + 24 - y + 1,
                           m_Pixmap, 11 - y, 24 - y, y, 1);
    }
    painter.drawPixmap(aX, 80 - 12 + 11, m_Pixmap, 0, 11, 12, 4);
}

void CPlayField::drawMidCenter(QPainter &painter, int aX)
{
    painter.drawPixmap(aX, 80 - 33 + 1,
                       (e_Direction == ENorth || e_Direction == EWest)
                       ? m_MiddleDistanceCenterBright : m_MiddleDistanceCenter);
}

void CPlayField::drawMidLeft(QPainter &painter, int aX)
{
    QPixmap m_Pixmap;

    m_Pixmap = (e_Direction == ENorth || e_Direction == EEast)
            ? m_MiddleDistanceLeftBright : m_MiddleDistanceLeft;
    for (int y = 0; y < 22; y++) {
        if (!y) {
            continue;
        }
        painter.drawPixmap(aX, 80 - 33 + y, m_Pixmap, 0, y, y, 1);
        painter.drawPixmap(aX, 80 - 33 + 66 - y, m_Pixmap, 0, 66 - y, y, 1);
    }
    painter.drawPixmap(aX, 80 - 33 + 22, m_Pixmap, 0, 23, 24, 23);
}

void CPlayField::drawMidRight(QPainter &painter, int aX)
{
    QPixmap m_Pixmap;

    m_Pixmap = (e_Direction == ESouth || e_Direction == EWest)
            ? m_MiddleDistanceRightBright : m_MiddleDistanceRight;
    for (int y = 0; y < 22; y++) {
        painter.drawPixmap(aX + 22 - y, 80 - 33 + y, m_Pixmap, 22 - y, y, y, 1);
        painter.drawPixmap(aX + 22 - y, 80 - 33 + 66 - y + 1,
                           m_Pixmap, 22 - y, 66 - y, y, 1);
    }
    painter.drawPixmap(aX, 80 - 33 + 22, m_Pixmap, 0, 22, 24, 24);
}

void CPlayField::drawCloseCenter(QPainter &painter)
{
    painter.drawPixmap(0, 0,
                       (e_Direction == ENorth || e_Direction == EWest)
                       ? m_CloseDistanceCenterBright : m_CloseDistanceCenter);
}

void CPlayField::drawCloseLeft(QPainter &painter)
{
    QPixmap m_Pixmap;

    m_Pixmap = (e_Direction == ENorth || e_Direction == EEast)
            ? m_CloseDistanceLeftBright : m_CloseDistanceLeft;
    for (int y = 0; y < 51; y++) {
        if (!y) {
            continue;
        }
        painter.drawPixmap(0, y, m_Pixmap, 0, y, y, 1);
        painter.drawPixmap(0, 160 - y, m_Pixmap, 0, 160 - y, y, 1);
    }
    painter.drawPixmap(0, 51, m_Pixmap, 0, 51, 50, 60);
}

void CPlayField::drawCloseRight(QPainter &painter)
{
    QPixmap m_Pixmap;

    m_Pixmap = (e_Direction == ESouth || e_Direction == EWest)
            ? m_CloseDistanceRightBright : m_CloseDistanceRight;
    for (int y = 0; y < 51; y++) {
        painter.drawPixmap(160 - y + 1, y, m_Pixmap, 51 - y - 1, y, y, 1);
        painter.drawPixmap(160 - y, 160 - y,
                           m_Pixmap, 51 - y - 1, 160 - y, y, 1);
    }
    painter.drawPixmap(110, 51, m_Pixmap, 0, 51, 50, 60);
}

CPlayField::~CPlayField()
{
    delete m_MainPixmap;
    delete m_GameTimer;
}
