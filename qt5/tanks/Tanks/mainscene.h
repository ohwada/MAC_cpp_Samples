#pragma once
/**
 * mainscene.h
 * 2022-06-01 K.OHWADA
 */

// original : https://github.com/magziim/Tanks

#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QGraphicsView>
#include <QGraphicsItem>
#include <QPainter>
#include "wall.h"
#include "tank.h"
#include "bullet.h"
#include "target.h"
#include <QSize>
#include <QWidget>
#include <string>


/**
 * class MainScene
 */
class MainScene : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MainScene( float width, float height, QWidget *parent = 0);


protected:
    void keyPressEvent(QKeyEvent *e);

signals:
  //  void signalDamage(int);
    void signalConnect(int, float);
    void openmenu();

private:
void playSoundFire();
static QList<QGraphicsItem *> target_tank1;//target list
static QList<QGraphicsItem *> target_tank2;//target list
    QGraphicsScene      *scene;     // Declaring the scene for rendering
    Tank* tank1;
    QTimer          *timer;
    Tank* tank2;
    QTimer          *timer2;
    float  scene_width;
    float  scene_height;

private slots:
    void slotBullet(int id, QPointF start,QPointF target);
     static void slothit(QGraphicsItem *item);

};

#endif // MAINSCENE_H
