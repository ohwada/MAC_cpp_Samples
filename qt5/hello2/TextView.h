#pragma once
/**
 * TextView.h
 * 2022-06-01 K.OHWADA
 */


#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QPaintEvent>
#include <QFont>
#include <QString>


/**
 * class TextView.h
 */

   class TextView
    {

public:
  	TextView();
  	~TextView();
    QGraphicsView* getView();
    void setFontSize(int size);
    void setText( float x, float y, QString str );

private:
    QString m_str;
    int m_font_size;
    float m_x;
    float m_y;

};