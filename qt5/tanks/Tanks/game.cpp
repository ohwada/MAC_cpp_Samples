/**
 * game.cpp
 * 2022-06-01 K.OHWADA
 */

// chang log
// 2022-06-01 K.OHWADA
 // #include "windows.h"
// added WIDTH ,  HEIGHT 
// added slotOpenMenu() 

// original : https://github.com/magziim/Tanks


#include  <QGuiApplication>
#include  <QDebug>
#include "game.h"
// #include "windows.h"


/**
 * constractor
 */
Game::Game(QWidget *parent) : QWidget(parent)
{
 //Get the size of the widget
    // virtual desktop setting QRect(1280, 0, 1280, 1024). 
    const int WIDTH = QGuiApplication::screens().at(0)->availableGeometry().width();
    const int HEIGHT = QGuiApplication::screens().at(0)->availableGeometry().height();

// game: w= 1440  h= 852
    // qDebug() << "game: w= " <<WIDTH << " h= " <<HEIGHT;

    QVBoxLayout* game_layout = new QVBoxLayout(NULL);
    game_layout->setContentsMargins(0, 0, 0, 0);
    game_layout->setSpacing(0);

  
    //widget with scene
    // Score, MainScene　in that order
    Score* score = new Score( WIDTH ,  HEIGHT );
    game_layout->addWidget(score);

    MainScene* main_scene = new MainScene( WIDTH ,  HEIGHT );
    game_layout->addWidget(main_scene);

    connect (main_scene,&MainScene::signalConnect,score,&Score::slotDamage);
    connect (score,&Score::signalEndOfTheGame,this,&Game::SlotEndOfTheGame);
    this->setLayout(game_layout);

    connect (main_scene,&MainScene::openmenu, this, &Game::slotOpenMenu);
}


/**
 * keyPressEvent
 */
void Game::keyPressEvent(QKeyEvent *e)
{
// Note:
// Not detect key event Here
 // intercepted by keyPressEvent  of mainscene
// emitt signal from mainscene
// when  keyPressEvent of the mainscene detect
// and receive with slotOpenMenu ()

    int key = e->key();
    // qDebug() << "game: key: " << key;

    if( key == Qt::Key_Escape)
        {
            // emit openmenu();
        }
}


/**
 * SlotEndOfTheGame
 */
void Game::SlotEndOfTheGame(int ID){
 emit GameOver(ID);
}


/**
 *   slotOpenMenu
 */
void Game::slotOpenMenu() {
    emit openmenu();
}

