#pragma once
 /**
 * targett.h
 * 2022-06-01 K.OHWADA
 */

// chang log
// 2022-06-01 K.OHWADA
// #include "windows.h"

// original : https://github.com/magziim/Tanks

#ifndef TARGET_H
#define TARGET_H

#include "item_base.h"

// #include "windows.h"
#include <QScreen>
#include <QGuiApplication>


 /**
 * class Target
 */
class Target : public ItemBase
{
    Q_OBJECT
public:
    explicit Target(QObject *parent = 0);
    ~Target();
 qreal angle; //angle

    QRectF boundingRect() const;
    QPainterPath shape() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);





};


#endif // TARGET_H
