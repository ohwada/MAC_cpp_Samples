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
    font.setWeight(QFont::Bold);

    QGraphicsScene *scene = new QGraphicsScene();
    QGraphicsTextItem *text = scene->addText(m_str);
    text->setFont(font);
    text->setPos(m_x, m_y);

    QGraphicsView *view = new QGraphicsView(scene);
    return view;
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
   void TextView::setText( float x, float y, QString str )
   {
        m_x = x;
        m_x = y;
        m_str = str;
  }


