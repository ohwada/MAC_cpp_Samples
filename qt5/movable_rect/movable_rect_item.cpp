/**
 * movable_rect_item.cpp
 * 2022-06-01 K.OHWADA
 */

// reference : https://blog-mk2.d-yama7.com/2019/07/20190726_qt_movable_item/

#include <QDebug>
#include "movable_rect_item.h"

const float X = 0;
const float Y = 0;
const float W = 50;
const float H = 50;

// pen width
const float PW = 2;

/**
 * constractor
 */
MovableRectItem::MovableRectItem()
{
    setRect(X, Y, W, H);
    this->init();
}


/**
 * constractor
 */
MovableRectItem::MovableRectItem(float x, float y, float width, float height) : QGraphicsRectItem(x, y, width, height)
{
    this->init();
}


/**
 * destractor
 */
MovableRectItem::~MovableRectItem()
{
    // none
}


/**
 * init
 */
void MovableRectItem::init()
{
    QPen pen(Qt::blue);
    pen.setWidth(PW);
    setPen(pen);
}


/**
 * mousePressEvent
 */
void MovableRectItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
}


/**
 * mouseMoveEvent
 */
void MovableRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    this->setPos(event->scenePos());
}


/**
 * mouseReleaseEvent
 */
void MovableRectItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
}

