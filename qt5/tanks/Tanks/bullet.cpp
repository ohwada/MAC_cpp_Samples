/**
 * bullet.cpp
 * 2022-06-01 K.OHWADA
 */

// chang log
// 2022-06-01 K.OHWADA
//  inheritance ItemBase
// added width height id to constractor
// hit directly without signalhit()


// original : https://github.com/magziim/Tanks

#include "bullet.h"

#include <QList>
#include <QGraphicsItem>
#include <QPolygonF>
#include <QGraphicsScene>
#include <QDebug>
#include <cmath>

static const double Pi = 3.14159265358979323846264338327950288419717;
static double TwoPi = 2.0 * Pi;


/**
 * constractor
 */
Bullet::Bullet(QObject *parent) : ItemBase(parent)
{
    setItemTpe(TYPE_BULLET);

    angle = 0;     // Setting the rotation angle of the graphic object
    setRotation(angle);     //Set the angle of rotation of the graphic object

}


/**
 * normalizeAngle
 */
static qreal normalizeAngle(qreal angle)
{
    while (angle < 0)
        angle += TwoPi;
    while (angle > TwoPi)
        angle -= TwoPi;
    return angle;
}


/**
 * constractor
 */
Bullet::Bullet(float width, float height, int id, QPointF start, QPointF target, QObject *parent)
    : ItemBase(parent)
{
    setItemTpe(TYPE_BULLET);

    scene_width = width;
    scene_height = height;
    shooter_id = id;

    this->setRotation(0);// Setting the initial reversal


    this->setPos(start);//Setting the starting position
    // Determine the trajectory of the bullet
    QLineF lineToTarget(start, target);
    // Angle of rotation towards the target
    qreal angleToTarget = ::acos(lineToTarget.dx() / lineToTarget.length());
    if (lineToTarget.dy() < 0)
        angleToTarget = TwoPi - angleToTarget;
    angleToTarget = normalizeAngle((Pi - angleToTarget) + Pi / 2);

    // Expand the bullets along the trajectory
    if (angleToTarget >= 0 && angleToTarget < Pi) {
        /// Rotate left
        setRotation(rotation() - angleToTarget * 180 /Pi);
    } else if (angleToTarget <= TwoPi && angleToTarget > Pi) {
        /// Rotate right
        setRotation(rotation() + (angleToTarget - TwoPi )* (-180) /Pi);
    }
    // Initializing the flight timer
    timerBullet = new QTimer();
    // And connect it to the slot to handle the flight of the bullet
    connect(timerBullet, &QTimer::timeout, this, &Bullet::slotTimerBullet);
    timerBullet->start(20);
}


/**
 * destractor
 */
Bullet::~Bullet()
{
    // none
}


/**
 * boundingRec
 */
QRectF Bullet::boundingRect() const
{
    return QRectF(0,0,2,4);
}


/**
 * paint
 */
void Bullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::black);
    painter->setBrush(Qt::black);
    painter->drawRect(0,0,2,4);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}


/**
 * slotTimerBullet
 */
void Bullet::slotTimerBullet()
{
 setPos(mapToParent(0, -10));


    /* We make a check to see if a bullet has stumbled on any
        * element in the graphic scene.
        * To do this, define a small area in front of the bullet,
        * in which we will search for elements
        * */
     QList<QGraphicsItem*> foundItems = 
    scene()->items(QPolygonF()
                                                            << mapToScene(0, 0)
                                                          << mapToScene(-1, -1)
                                                        << mapToScene(1, -1));
       /* Then we check all the elements.
        * One of them will be Bullet herself and the Hero - we do nothing with them.
        * And with the rest, call SIGNAL
        * */
      foreach (QGraphicsItem *item, foundItems) 
{

    // Casting an object from the list into the Tank class
    ItemBase *base = qgraphicsitem_cast <ItemBase*> (item);
    int type = base->itemType() ;   
    int id = base->id() ;
// qDebug() << "type: " << type << " id: " << id;

// if target tank, emit signal
        if ( (type == TYPE_TANK )&&(id != shooter_id) ) {
            Tank *tank = qgraphicsitem_cast <Tank*> (item);
            // emit signalhit(item);
            tank->hit(2);
            this->deleteLater();    //We destroy the bullet
        }
     }

/* Checking field out of bounds
 * If the bullet flies out of the specified boundaries, then the bullet must be destroyed
 * */
    if(this->x() < 0){
        this->deleteLater();
    }
    if(this->x() > scene_width ){
        this->deleteLater();
    }

    if(this->y() < 0){
        this->deleteLater();
    }
    if(this->y() > scene_height ){
        this->deleteLater();
    }
}


