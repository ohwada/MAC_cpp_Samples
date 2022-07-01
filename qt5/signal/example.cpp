/**
 * example.cpp
 * 2022-06-01 K.OHWADA
 */

// reference : https://www.qt.io/ja-jp/blog/2010/07/20/create-signals-and-slots


#include <QSlider>     
#include <QPushButton> 
#include "example.h"
#include "object.h" 


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

    Object *object1 = new Object(this); 

    object1->setObjectName("object 1"); 

    Object *object2 = new Object(this); 

    object2->setObjectName("object 2"); 

// connect slider signal valueChanged (int) 
// to slot setValue (int) in object1
    connect(slider, SIGNAL(valueChanged(int)), object1, SLOT(setValue(int))); 

    connect(object1, SIGNAL(valueChanged(int)), object2, SLOT(setValue(int)));

// close when the button is pressed
    connect( button, SIGNAL(clicked()), this, SLOT(close()) );
}

