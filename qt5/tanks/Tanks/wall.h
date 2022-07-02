#pragma once
 /**
 * wall.h
 * 2022-06-01 K.OHWADA
 */

// original : https://github.com/magziim/Tanks

#ifndef WALL_H
#define WALL_H

#include "item_base.h"

 /**
 * class Wall
 */
class Wall : public ItemBase
{
public:
    explicit Wall(QObject *parent = 0);
    ~Wall();

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // WALL_H
