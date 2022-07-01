/**
 * object.cpp
 * 2022-06-01 K.OHWADA
 */

//reference : https://www.qt.io/ja-jp/blog/2010/07/20/create-signals-and-slots

#include <QDebug> 
#include "object.h"


/**
 * constractor
 */
Object::Object(QObject *parent)
    : QObject(parent), m_value(0)  
{
	// none
}


/**
 * value
 */
int Object::value() const 
{
    return m_value;
}


/**
 * setValue
 */
void Object::setValue(int value) 
{
   if (m_value == value) return; 

    m_value = value;

   qDebug() << "value of" << objectName() << "is changed to" << m_value; 

    emit valueChanged(m_value); 
}

