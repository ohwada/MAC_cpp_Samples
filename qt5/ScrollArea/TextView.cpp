/**
 *TextView.cpp
 * 2022-06-01 K.OHWADA
 */


#include "TextView.h"


/**
 *  constractor
 */
TextView::TextView()
{
    // none
}


/**
 *  destractor
 */
TextView::~TextView()
{
    // none
}


/**
 *  getView
 */
QGraphicsView* TextView::getView()
{
    QFont font;
    font.setPixelSize(m_font_size);
  
    QGraphicsScene *scene = new QGraphicsScene(0, 0, m_scene_width, m_scene_height);

    QGraphicsTextItem *text = scene->addText(m_str);
    text->setFont(font);
    text->setTextWidth( m_text_width );

    QGraphicsView *view = new QGraphicsView(scene);
    return view;
}


/**
 *  set   SceneSize
 */
void TextView::setSceneSize(float width, float height)
{
    m_scene_width = width;
    m_scene_height = height;
}


/**
 *  setFontSize
 */
void TextView::setFontSize(int size)
{
    m_font_size = size;
}


/**
 *  setText
 */
   void TextView::setText( float width, QString str )
   {
        m_text_width = width;
        m_str = str;
  }

