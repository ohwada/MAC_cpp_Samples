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
    void setSceneSize(float width, float height);
    void setFontSize(int size);
    void setText( float width, QString str );

private:
    QString m_str;
    float m_scene_width;
    float m_scene_height;
    int m_font_size;
    float m_text_width;

};