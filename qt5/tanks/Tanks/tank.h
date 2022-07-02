#pragma once
 /**
 * tank.h
 * 2022-06-01 K.OHWADA
 */

// original : https://github.com/magziim/Tanks

#ifndef TANK_H
#define TANK_H

#include "item_base.h"
#include "target.h"


 /**
 * class Tank
 */
class Tank : public ItemBase
{
    Q_OBJECT
public:
    explicit Tank(int id, float width, float height, QObject *parent = 0);
    ~Tank();
    Target* target;
    void hit(int damdge);
    void turnLeft();
    void turnRight();
    void moveForward();
    void moveBackword();
    void fire();


signals:
 void signalBullet(int id, QPointF start ,QPointF target);
 void signalDamage(int id, float health);

protected:
    QPainterPath shape() const;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    void checkBorder();
    qreal angle; //angle
    int health;
    float  scene_width;
    float  scene_height;
};

#endif // TANK_H
