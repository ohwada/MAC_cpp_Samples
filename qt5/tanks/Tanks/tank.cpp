/**
 * tank.cpp
 * 2022-06-01 K.OHWADA
 */

// chage log
// 2022-06-01 K.OHWADA
//  inheritance ItemBase
// added id width height to constractor
// changed to call from keyPressEvent 
// instead of GetAsyncKeyState
//  added id to signalBullet

// original : https://github.com/magziim/Tanks

#include <QGraphicsScene>
#include <QDebug>
#include "tank.h"
#include "param.h"

// step of forword , back word
const   qreal  STEP = 5;

// step of rotate
const   qreal  DEG = 10;


/**
 * constractor
 */
Tank::Tank(int id, float width, float height, QObject *parent) 
: ItemBase(parent)
{
    setItemTpe(TYPE_TANK);
    setId(id);

    scene_width = width;
    scene_height = height;

    angle = 0;     //   Setting the rotation angle of the graphic object
    setRotation(angle);  // Set the angle of rotation of the graphic object
    target= new Target();
    health = MAX_HEALTH;
}


/**
 * destractor
 */
Tank::~Tank()
{
    // none
}


/**
 * boundingRec
 */
QRectF Tank::boundingRect() const
{
    return QRectF(-20, -25, 40, 50);   // Limiting the area in which the tank lies
}


/**
 * shape
 */
QPainterPath Tank::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}


/**
 * paint
 */
void Tank::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    int id = this->id();
    if ( id == 1) {
       painter->setBrush(Qt::blue);
    } else if ( id == 2) {
       painter->setBrush(Qt::green);
    }

    painter->drawRect(-15,-25,30,40);//body
    painter->setBrush(Qt::black);
    painter->drawRect(-20,-20,5,30);//left wheel
    painter->drawRect(15,-20,5,30);//right wheel
    painter->drawRect(-5,-5,10,30);//gun
    target->setPos(mapToParent(0, 2000));


    Q_UNUSED(option);
    Q_UNUSED(widget);
}


/**
 * turnLeft
 */
void Tank::turnLeft()
{
    // qDebug() << "turnLeft";

// rotate 10 degrees to the left
    angle -= DEG;    
    setRotation(angle); 

    target->angle -= DEG;
    target->setRotation(target->angle);

// if tank collide with the wall
// rotate 10 degrees to the right
    if(!(this->scene()->collidingItems(this).isEmpty())){
            angle += DEG; 
            setRotation(angle);
    }
    checkBorder();
}


/**
 * turnRight
 */
void Tank::turnRight()
{
   // qDebug() << "turnRight";

// rotate 10 degrees to the right
    angle += 10;        // Set the rotation 10 degrees to the right
    setRotation(angle); // Rotating the object
    target->angle += DEG;        // Set the rotation 10 degrees to the left
      target->setRotation(target->angle);
                /* Checking for a collision
                 * if a collision has occurred,
                 * then we return the hero back to the starting point
                 * */
    if(!scene()->collidingItems(this).isEmpty()){
                    angle -= DEG;// Set the rotation 10 degrees to the right
                    setRotation(angle); // Rotating the object
    }
    checkBorder();
}


/**
 * moveForward
 */
void Tank::moveForward()
{
   // qDebug() << "moveForward";

// forward 5px
// convert this item's coordinate system, to its parent's coordinate system
    setPos(mapToParent(0, STEP));

// if tank collide with the wall
// backward 5 px
    if(!scene()->collidingItems(this).isEmpty()){
                    setPos(mapToParent(0, -STEP));
    }
    checkBorder();
}


/**
 * moveBackward
 */
void Tank::moveBackword()
{
   // qDebug() << "moveBackward";

// backward 5px
    setPos(mapToParent(0, -STEP)); 

// if tank collide with the wall
// forward 5 px
    if(!scene()->collidingItems(this).isEmpty()){
              setPos(mapToParent(0, STEP));
    }
    checkBorder();
}


/**
 *  checkBorder
 */
void Tank::checkBorder()
{

    if(this->x() < 0){
        this->setX(1);       //left
    }
    if(this->x() > scene_width){
        this->setX(scene_width- 1);        //right
    }
    if(this->y()< 0){
        this->setY(1);       //up
    }
    if(this->y()>  scene_height){
        this->setY(scene_height - 1);        //down
    }
}


/**
 * fire
 */
void Tank::fire()
{
   // qDebug() << "fire";

    emit signalBullet( id(),
    mapToScene(0,25), QPointF(target->x(), target->y()));
}


/**
 * hit
 */
void Tank::hit(int damage)
{
    health -= damage;   // Reduce Target Health
    emit signalDamage( id(), (float)health );
    if(health <= 0) this->deleteLater();
}


