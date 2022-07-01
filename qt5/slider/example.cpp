/**
 * example.cpp
 * 2022-06-01 K.OHWADA
 */

// reference : https://www.qt.io/ja-jp/blog/2010/05/21/qwidget

#include <QSlider>     
#include <QPushButton> 
#include "example.h"

/**
 * constractor
 */
Example::Example(QWidget *parent)
    : QWidget(parent)
{
    // none
}


/**
 * constractor
 */
Example::Example()
{

    QSlider *slider = new QSlider(Qt::Horizontal, this);  

    slider->setGeometry(10, 10, 200, 20);               

    QPushButton *button = new QPushButton("Close", this); 

    button->setGeometry(10, 40, 200, 30);  

}

