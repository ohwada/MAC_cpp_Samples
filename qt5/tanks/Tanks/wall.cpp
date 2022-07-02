 /**
 * wall.cpp
 * 2022-06-01 K.OHWADA
 */

// chage log
// 2022-06-01 K.OHWADA
//  inheritance ItemBase

// original : https://github.com/magziim/Tanks

#include "wall.h"


 /**
 * constractor
 */
Wall::Wall(QObject *parent) : ItemBase(parent)
{
    setItemTpe(TYPE_WALL);
}


 /**
 * destractor
 */
Wall::~Wall()
{
    // none
}


 /**
 * boundingRect
 */
QRectF Wall::boundingRect() const
{
// We limit the area in which the triangle lies
    return QRectF(0, 0, 51, 51);
}


 /**
 * paint
 */
void Wall::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    //QImage texture_image1(file_path + "/forest.jpg");
    //QString file_path = PRO_FILE_PWD;
    //QImage texture_image1(":/textures/images/box.jpg");
    QImage texture_image(":/textures/images/bricks.png");

    //QImage texture_image;

    /*if(is_box) {
       texture_image = texture_image1;
    } else {
       texture_image = texture_image2;
    }*/

        painter->drawImage(QRectF(0, 0, 51, 51), texture_image);

        //painter->drawRect(0, 0, 50, 50);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
