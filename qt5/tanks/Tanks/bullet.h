#pragma once
 /**
 * bullet.h
 * 2022-06-01 K.OHWADA
 */

// chang log
// 2022-06-01 K.OHWADA
 // #include "windows.h"

// original : https://github.com/magziim/Tanks

#ifndef BULLET_H
#define BULLET_H

#include "item_base.h"

#include <QTimer>

#include "tank.h"
// #include "windows.h"


 /**
 * class Bullet
 */
class Bullet : public ItemBase
{
    Q_OBJECT
public:
    explicit Bullet(QObject *parent = 0);
    explicit Bullet(float width, float height, int id, QPointF start, QPointF target, QObject *parent = 0);
    ~Bullet();

signals:
    void signalhit(QGraphicsItem *item);

public slots:

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QTimer *timerBullet; // Bullet timer processing
    qreal angle;
    Target *target;
   float  scene_width;
    float  scene_height;
    int shooter_id;

private slots:
    void slotTimerBullet(); // Slot for processing bullet flight
};

#endif // BULLET_H

