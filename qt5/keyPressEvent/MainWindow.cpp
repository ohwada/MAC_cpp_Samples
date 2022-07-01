/**
 * MainWindpw.cpp
 * 2022-06-01 K.OHWADA
 */


#include <QDebug>
#include "MainWindow.h"
#include "upper_lower.h"


/**
 *  constractor
 */
MainWindow::MainWindow()
{
	// none
}


// debug output the pressed key name
 // other keys output hexadecimal numbers
 void MainWindow::keyPressEvent(QKeyEvent *pEvent)
 {
    int key = pEvent->key();

    switch (key)
    {
       case Qt::Key_Escape:
          qDebug() << "Esc keyPress";
          break;
       case Qt::Key_Return:
          qDebug() << "Return keyPress";
          break;
       case Qt::Key_Enter:
          qDebug() << "Enter(keypad) keyPress";
          break;
       case Qt::Key_Home:
          qDebug() << "Home keyPress";
          break;
       case Qt::Key_Left:
          qDebug() << "Left keyPress";
          break;
       case Qt::Key_Right:
          qDebug() << "Right keyPress";
          break;
       case Qt::Key_Up:
          qDebug() << "Up keyPress";
          break;
       case Qt::Key_Down:
          qDebug() << "Down keyPress";
          break;
       case Qt::Key_Space:
          qDebug() << "Space keyPress";
          break;
       case Qt::Key_F1:
          qDebug() << "F1 keyPress";
          break;
       case Qt::Key_0:
          qDebug() << "0(keypad) keyPress";
          break;
       default:
            if( isAlphaNumerical(key) ){
                qDebug("keyPress %c", key);
            } else {
                qDebug("keyPress %x", key);
            }
          break;
    }
 }

