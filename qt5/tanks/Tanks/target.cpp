/**
 * taeget.cpp
 * 2022-06-01 K.OHWADA
 */

// chage log
// 2022-06-01 K.OHWADA
//  inheritance ItemBase

// original : https://github.com/magziim/Tanks

#include "target.h"


/**
 * constractor
 */
Target::Target(QObject *parent) :
    ItemBase(parent)
{
    setItemTpe(TYPE_TARGET);

    angle = 0;     // Setting the rotation angle of the graphic object
    setRotation(angle);     // Set the angle of rotation of the graphic object
}

/**
 * destractor
 */
Target::~Target()
{
    // none
}


/**
 * boundingRec
 */
QRectF Target::boundingRect() const
{
    return QRectF(-20, -25, 40, 50);
}


/**
 * shape
 */
QPainterPath Target::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}


/**
 * paint
 */
void Target::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{painter->setBrush(Qt::black);
    painter->drawEllipse(-5,-5,10,10);
    painter->setBrush(Qt::red);
painter->drawRect(-5,-1,10,2);//horizontal line
painter->drawRect(-1,-5,2,10);//vertical line

    Q_UNUSED(option);
    Q_UNUSED(widget);
}


