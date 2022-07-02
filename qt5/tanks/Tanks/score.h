#pragma once
 /**
 * score.h
 * 2022-06-01 K.OHWADA
 */

// original : https://github.com/magziim/Tanks

#ifndef SCORE_H
#define SCORE_H


#include <QScreen>
#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QPalette>
#include <QLabel>
#include <QStyleOptionGraphicsItem>
#include <fstream>
class Score : public QWidget
{
    Q_OBJECT
public:
    explicit Score(float width, float height);

protected:
    void paintEvent(QPaintEvent *event);

signals:
void signalEndOfTheGame(int ID);
public slots:
void slotDamage( int id, float health );
protected:
void resize(int ID);
private:
void resize(int id, float x, float y, float width, float height );

    const int WIDTH = QGuiApplication::screens().at(0)->availableGeometry().width();
    const int HEIGHT = ::QGuiApplication::screens().at(0)->availableGeometry().height();
    const int LENGTH = WIDTH / 4;

    int health;
    int length;
    float hp1_x;
    float hp2_x;
    QRectF hp1;
    QRectF hp2;

};


#endif // SCORE_H
