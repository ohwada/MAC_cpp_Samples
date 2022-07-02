/**
 * mainscene.cpp
 * 2022-06-01 K.OHWADA
 */

// chang log
// 2022-06-01 K.OHWADA
// changed to call tank from keyPressEvent
// instead of GetAsyncKeyState
// changed the coordinate origin to (0, 0)
// added width height to constractor
// place tanks in random positions, avoiding walls
//  added id to :slotBullet
// hit in bullet directly without slothit()
// PROG_DIR  in param.h
// emit openmenu();
// added playSoundFire()

// original : https://github.com/magziim/Tanks

#include "mainscene.h"
#include "map_creator.h"

#include <QApplication>
#include <QKeyEvent>
#include <QDebug>

#include "rand.h"
#include "file_util.h"
#include "sound.h"
#include "param.h"


QList<QGraphicsItem *> MainScene::target_tank1;
QList<QGraphicsItem *> MainScene::target_tank2;


/**
 * constractor
 */
MainScene::MainScene( float width, float height, QWidget *parent)
    : QGraphicsView(parent) 
{
    scene_width = width;
    scene_height = height;

// Initialize the scene for rendering
    scene = new QGraphicsScene();   

    this->resize(scene_width, scene_height);

//Set the scene size
    int sx = 0;
    int sy =  0;
    scene->setSceneRect(sx, sy, scene_width, scene_height);

    // scene->setFlag(QGraphicsItem::ItemIsFocusable, true);
    this->setScene(scene);

    this->setRenderHint(QPainter::Antialiasing); //Use Antialiasing
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Disable the horizontal scrollbar
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);   // Disable the vertical scrollbar
    this->setAlignment(Qt::AlignCenter);                        // Binding the content to the center
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);


    QBrush back_brush(QColor(255, 243, 240)); //bricks & box
    //QBrush back_brush(QColor(224, 255, 224)); //forest

    QPen pen(Qt::black);
    pen.setWidth(1);

    scene->setBackgroundBrush(back_brush);

    scene->addLine(sx, sy, scene_width, sy, pen);//upper bound
    scene->addLine(sx, scene_height,scene_width, scene_height, pen);//lower bound
    scene->addLine(sx, sy, sx, scene_height, pen);//left bound
    scene->addLine(scene_width, sy, scene_width, scene_height, pen);//right bound


    MapCreator map_creator;


    std::string map_dir = PROG_DIR + ("maps/");
    std::string map_file = map_dir + std::string("map_1_2.txt");

    if( ! existsFile(map_file) ){
        qDebug() << "not found: " << map_file.c_str();
    }

    map_creator.setFile(map_file);

    map_creator.CreateMap(scene);

    tank1 = new Tank(1, scene_width, scene_height );
    tank2 = new Tank(2, scene_width, scene_height );

Target* target1=new Target();
tank1->target = target1;
scene->addItem(tank1->target);
target_tank1.push_back(tank1);

Target* target2=new Target();
tank2->target = target2;
scene->addItem(tank2->target);
target_tank2.push_back(tank2);

scene->addItem(tank1);   // Add a tank to the scene
scene->addItem(tank2);
// tank1->setPos(-690,-300);  // Place the tank in the center of the scene


// place tanks in random positions, avoiding walls
//QRectF r = tank1->boundingRect(); 

// tank size
const float TW = 40;
const float TH = 50;


// tank1
// place in the upper right
float cx = sx + scene_width/ 2.0;
float cy = sy + scene_height / 2.0;
float x1_min = sx  + scene_width/ 3.0;
float x1_max = cx;
float y1_min = sy + scene_height / 3.0;
float y1_max = cy;

int x1_renge = (x1_max - x1_min)/TW;
int y1_renge = (y1_max - y1_min)/TH;

// tank1: xmin:  479.333  xmax:  794  ymin  259  ymax:  463.5
// qDebug() << "tank1: xmin: " << x1_min << " xmax: " << x1_max << " ymin " << y1_min << " ymax: " << y1_max;

float x, y;
int cnt = 0;
while(1)
{
    if(cnt>100){
        break;
    }
    cnt++;
    int xd = genRandInt(0, x1_renge);
    int yd = genRandInt( 0, y1_renge);
    x = x1_min + xd*TW;
    y = y1_min + yd*TH;
    tank1->setPos(x, y); 
// if tank not collide with the wall
    if( tank1->scene()->collidingItems(tank1).isEmpty() ){
        break;
    }
   }

   qDebug() << "tank1: " << cnt << " x: "  << x << " y: " << y;

// tank2
// place in the lower left
float x2_min = cx;
float x2_max = sx + scene_width *(9.0 / 10.0) ;
float y2_min = cy;
float y2_max = sy + scene_height *(9.0 /10.0);

int x2_renge = (x2_max - x2_min)/TW;
int y2_renge = (y2_max - y2_min)/TH;

// tank2: xmin:  719  xmax:  1294.2  ymin  388.5  ymax:  699.3
// qDebug() << "tank2: xmin: " << x2_min << " xmax: " << x2_max << " ymin " << y2_min << " ymax: " << y2_max;


cnt = 0;
while(1)
{
    if(cnt>100){
        break;
    }
    cnt++;
    int xd = genRandInt(0, x2_renge);
    int yd = genRandInt(0, y2_renge);
    x = x2_min + xd*TW;
    y = y2_min + yd*TH;
    tank2->setPos(x, y); 
// if tank not collide with the wall
    if( tank2->scene()->collidingItems(tank2).isEmpty() ){
        break;
    }
}

   qDebug() << "tank2: " << cnt << " x: " << x << " y: " << y;


    this->setScene(scene);
    connect (tank1, &Tank::signalBullet, this, &MainScene::slotBullet);
    connect (tank2, &Tank::signalBullet, this, &MainScene::slotBullet);

    connect (tank1,&Tank::signalDamage,this,&MainScene::signalConnect);
    connect (tank2,&Tank::signalDamage,this,&MainScene::signalConnect);
}


/**
 * :slotBullet
 */
void MainScene::slotBullet(int id, QPointF start,QPointF target)
{
//Add a bullet to the scene
   Bullet *bullet = new Bullet(scene_width,  scene_height, id, start, target);
    scene->addItem(bullet);

    // connect (bullet,&Bullet::signalhit, this, &MainScene::slothit);
}


/**
 * slothit
 */
void MainScene::slothit(QGraphicsItem *item)
{
     Q_UNUSED(item);
}


 /**
 * :keyPressEvent
 */
void MainScene::keyPressEvent(QKeyEvent *e)
{
// Note:
// key event of ESC key is propagated to 
// game and mainwindow as a signal

    int key = e->key();
    // qDebug() << "mainscene: key: " << key;

    switch(key)
{
    case Qt::Key_Left:
        // qDebug() << "left";
        tank1->turnLeft();
        break;
    case Qt::Key_Right:
        // qDebug() << "right";
        tank1->turnRight();
        break;
    case Qt::Key_Up:
        // qDebug() << "up";
        tank1->moveForward();
        break;
    case Qt::Key_Down:
        // qDebug() << "down";
        tank1->moveBackword();
        break;
    case Qt::Key_K:
        // qDebug() << "K";
        tank1->fire();
        playSoundFire();
        break;
    case Qt::Key_A:
        // qDebug() << "A";
        tank2->turnLeft();
        break;
    case Qt::Key_D:
        // qDebug() << "D";
        tank2->turnRight();
        break;
    case Qt::Key_W:
        // qDebug() << "W";
        tank2->moveForward();
        break;
    case Qt::Key_S:
        // qDebug() << "S";
        tank2->moveBackword();
        break;
    case Qt::Key_C:
        // qDebug() << "C";
        tank2->fire();
        playSoundFire();
        break;
    case Qt::Key_Escape:
        // qDebug() << "ESC";
            emit openmenu();
        break;
} // switch
 
}


 /**
 * :playSoundFire
 */
void MainScene::playSoundFire()
{
    if( existsFile(CMD_PLAY) ){
        if( existsFile(SND_FIRE) ){
            playSound( (char *)SND_FIRE );
        } else {
            qDebug() << "not found: " << SND_FIRE;
        }
    } else {
            qDebug() << "not found: " << CMD_PLAY;
    }

}
