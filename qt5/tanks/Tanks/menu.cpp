 /**
 * menu.cpp
 * 2022-06-01 K.OHWADA
 */

// original : https://github.com/magziim/Tanks


#include <QDebug>
#include "menu.h"


 /**
 * constractor
 */
Menu::Menu(QWidget *parent) : QWidget(parent)
{

    QVBoxLayout* menu_layout = new QVBoxLayout();
    QPushButton* play = new QPushButton("Play");
    QPushButton* settings = new QPushButton("Settings");
    QPushButton* exit = new QPushButton("Exit");

    int WINDOW_WIDTH = QGuiApplication::screens().at(0)->availableGeometry().width();
    int WINDOW_HEIGHT = QGuiApplication::screens().at(0)->availableGeometry().height();

// menu: w:  1440  h:  852
// qDebug() << "menu: w: " << WINDOW_WIDTH << " h: " << WINDOW_HEIGHT;

    this->setAutoFillBackground(true);
    QPalette palette = this->palette();

    palette.setBrush(QPalette::Window, QBrush
                     (QPixmap(":/bg/images/menu.png").scaled(QSize(WINDOW_WIDTH, WINDOW_HEIGHT), Qt::IgnoreAspectRatio)));
    this->setPalette(palette);

 int left = WINDOW_WIDTH/3;
    int top = WINDOW_HEIGHT/4;
    int right = WINDOW_WIDTH/3;
    int bottom = WINDOW_HEIGHT/4;

 // left;  480  top: 213  right:  480  bottom:  213
// qDebug() << "left; " << left << " top:" << top << " right: " << right << " bottom: "<< bottom;

    menu_layout->setContentsMargins(left, top, right, bottom);
    play->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    settings->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    exit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    menu_layout->addWidget(play);
    menu_layout->addWidget(settings);
    menu_layout->addWidget(exit);

    this->setLayout(menu_layout);

    connect(play, &QPushButton::clicked, this, &Menu::play);
    connect(settings, &QPushButton::clicked, this, &Menu::settings);
    connect(exit, &QPushButton::clicked, this, &Menu::exit);
}
