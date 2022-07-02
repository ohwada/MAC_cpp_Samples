// chang log
// 2022-06-01 K.OHWADA
// debug log


#include <QDebug>
#include "gamemenu.h"

GameMenu::GameMenu(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout* menu_layout = new QVBoxLayout();
    QPushButton* play = new QPushButton("Play");
    QPushButton* newgame = new QPushButton("New Game");
    QPushButton* settings = new QPushButton("Settings");
    QPushButton* exit = new QPushButton("Exit");
    //play->setEnabled(false);
    //settings->setEnabled(false);

// get the size of the window
    int WINDOW_WIDTH = QGuiApplication::screens().at(0)->availableGeometry().width();
    int WINDOW_HEIGHT = QGuiApplication::screens().at(0)->availableGeometry().height();

// gamemenu: w:  1440  h:  852
    // qDebug() << "gamemenu: w: " << WINDOW_WIDTH << " h: " << WINDOW_HEIGHT;

    this->setAutoFillBackground(true);
    QPalette palette = this->palette();

    //QString file_path = PRO_FILE_PWD;
    palette.setBrush(QPalette::Window, QBrush
                     (QPixmap(":/bg/images/gamemenu.jpg").scaled(QSize(WINDOW_WIDTH, WINDOW_HEIGHT), Qt::IgnoreAspectRatio)));
    this->setPalette(palette);

    int left = WINDOW_WIDTH/3;
    int top = WINDOW_HEIGHT/5;
    int right = WINDOW_WIDTH/3;
    int bottom = WINDOW_HEIGHT/5;

// left;  480  top: 170  right:  480  bottom:  170
    // qDebug() << "left; " << left << " top:" << top << " right: " << right << " bottom: "<< bottom;
    menu_layout->setContentsMargins(left, top, right, bottom);

    play->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    newgame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    settings->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    exit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    menu_layout->addWidget(play);
    menu_layout->addWidget(newgame);
    menu_layout->addWidget(settings);
    menu_layout->addWidget(exit);

    this->setLayout(menu_layout);

    connect(play, &QPushButton::clicked, this, &GameMenu::play);
    connect(newgame, &QPushButton::clicked, this, &GameMenu::newgame);

// not found GameMenu::settings
    connect(settings, &QPushButton::clicked, this, &GameMenu::settings);

    connect(exit, &QPushButton::clicked, this, &GameMenu::exit);
}


