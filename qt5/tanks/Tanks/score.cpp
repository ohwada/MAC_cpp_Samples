 /**
 * score.h
 * 2022-06-01 K.OHWADA
 */

// chang log
// 2022-06-01 K.OHWADA
// added width height to constractor
// added id, x, y to resize

// original : https://github.com/magziim/Tanks

#include <QDebug>
#include "score.h"
#include "param.h"


// label size
const float W = 100;
const float H = 100;



 /**
 * constractor
 */
Score::Score(float width, float height)
{
    length = width/4;
    Q_UNUSED(height);

// label size
const float LH = H/2;

// font size
const int SIZE = 20;

    health= MAX_HEALTH;

    QLabel *label1 = new QLabel(this);
    label1->setFrameStyle(QFrame::Plain | QFrame::Box);
    label1->setStyleSheet("background-color:red;");
    label1->setText("Player1");
    label1->setAlignment(Qt::AlignTop | Qt::AlignCenter);
    label1->setFixedHeight(LH);
    QFont font1= label1->font();
    font1.setPixelSize(SIZE);
    label1->setFont(font1);

    float labe1_x = 0;
    label1->setGeometry( labe1_x, 0,W,H );

     hp1_x  =     labe1_x + W;
    float w1 = length*(health/MAX_HEALTH);
    resize( 1, hp1_x, 0, w1,  this->height() );

    QLabel *label2 = new QLabel(this);
    label2->setFrameStyle(QFrame::Plain | QFrame::Box);
    label2->setStyleSheet("background-color:red;");
    label2->setText("Player2");
    label2->setAlignment(Qt::AlignTop | Qt::AlignCenter);
    label2->setFixedHeight(LH);
    QFont font2= label2->font();
    font2.setPixelSize(SIZE);
    label2->setFont(font2);

    float label2_x = 2*length;
    label2->setGeometry( label2_x, 0, W, H );

    hp2_x =  label2_x + W;
    float w2 = length*(health/ MAX_HEALTH);
    resize( 2, hp2_x, 0, w2, this->height() );

    QPalette p(palette());
    p.setColor(QPalette::Window, QColor(255, 243, 240)); //bricks & box
    //p.setColor(QPalette::Window, QColor(224, 255, 224)); //forest

    this->setAutoFillBackground(true);
    this->setPalette(p);

    this->setFixedHeight(LH);
}

 /**
 * paintEvent
 */
void Score::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter1(this);
    QPainter painter2(this);

        painter1.save();
        painter1.setBrush(Qt::blue);
        if(!hp1.isNull())
            painter1.drawRect(hp1);
        painter1.restore();

        painter2.save();
        painter2.setBrush(Qt::green);
        if(!hp2.isNull())
            painter2.drawRect(hp2);
        painter2.restore();
}


 /**
 * slotDamag
 */
void Score::slotDamage(int id, float health)
{
   std::ofstream fout;

// qDebug()  << " id: " << id << " helth: " << health;

   if(id == 1){
        float w1 = length*(health/MAX_HEALTH);
        resize( hp1_x,  0, w1, this->height(),1);
        if(health<=0){
              std::ofstream fout;
                fout.open("Results.txt");
                fout << "Player2 WON!!!!";
                emit signalEndOfTheGame(2);
           }
   }
   else if(id==2){
        float w2 = length*(health/MAX_HEALTH);
        resize(  hp2_x, 0, w2 ,this->height(), 2);
        if(health<=0){
                fout.open("Results.txt");
                fout << "Player1 WON!!!!";
                emit signalEndOfTheGame(1);
           }
   }
   fout.close();
}


 /**
 * resize
 */
void Score::resize(int id, float  x, float y,  float width, float height)
{
    if (width < 0){
        width = 0;
    }
    if(id == 1){
        hp1 = QRectF(x, y, width, height);
    }else if(id == 2){
        hp2 = QRectF(x,  y,  width, height);
    }
    update();
}
