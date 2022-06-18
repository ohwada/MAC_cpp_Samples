/**
 *  MyGraphicsView.cpp
 * 2022-06-01 K.OHWADA
 */

// reffrence : https://mf-atelier.sakura.ne.jp/mf-atelier2/qt_image/


#include <QPainter>
#include <QTransform>

#include "MyGraphicsView.h"


/**
 *  constractor
 */
MyGraphicsView::MyGraphicsView()
{
    // none
}


/**
 *  destractor
 */
MyGraphicsView::~MyGraphicsView()
{
    // none
}


/**
 *  paintEvent
 */
// paintEvent() function is a virtual function that is called when redrawing.
// so, override this function and write the drawing part
// warning: unused parameter 'event'
  void MyGraphicsView::paintEvent( QPaintEvent *event )
   {
    QPainter widgetpainter( viewport() );

    QTransform tr;
    widgetpainter.setWorldTransform(tr);
   
// resize the drawing image to fit the size of the widget.
    QImage qimg = m_img.scaled(
   		viewport()->width(),
   		viewport()->height(),
  		Qt::KeepAspectRatio,Qt::FastTransformation);
   	widgetpainter.drawImage( 0, 0, qimg );
  }


/**
 *  setImg
 */
   void MyGraphicsView::setImg( QImage &img )
   {
  	m_img = QImage( img );
  	viewport()->update();
  }