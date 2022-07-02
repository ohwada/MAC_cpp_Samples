#pragma once
 /**
 * item_base.h
 * 2022-06-01 K.OHWADA
 */

#ifndef ITEM_BASE_H
#define ITEM_BASE_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QBrush>
#include <QImage>
#include <QFile>
#include <QPixmap>
#include <QLabel>
#include <QMessageBox>


const int TYPE_TANK = 1;
const int TYPE_TARGET = 2;
const int TYPE_BULLET = 3;
const int TYPE_WALL = 4;


 /**
 * class ItemBase
 */
class ItemBase : public QObject, public QGraphicsItem
{
public:
    ItemBase(QObject *parent = 0);
    ~ItemBase();
    int itemType();
    int id();

protected:
    void setItemTpe(int type);
    void setId(int id);
    int m_type;
    int m_id;
};

#endif // ITEM_BASE_H
