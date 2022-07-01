#pragma once
/**
 * movable_rect_item.h
 * 2022-06-01 K.OHWADA
 */

// rference : https://blog-mk2.d-yama7.com/2019/07/20190726_qt_movable_item/

#ifndef MOVABLE_GRAPHICS_ITEM_H
#define MOVABLE_GRAPHICS_ITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>


/**
 * class MovableRectItem
 */
class MovableRectItem : public QGraphicsRectItem
{


public:
    MovableRectItem();
    ~MovableRectItem();
    MovableRectItem(float x, float y, float width, float height);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    void init();

};

#endif // MOVABLE_RECT_ITEM_H

