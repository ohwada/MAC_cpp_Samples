#pragma once
/**
 *  MyGraphicsView.h
 * 2022-06-01 K.OHWADA
 */

// reffrence : https://mf-atelier.sakura.ne.jp/mf-atelier2/qt_image/


#include <QGraphicsView>
#include <QPaintEvent>

   
   class MyGraphicsView :
    public QGraphicsView
    {
    	Q_OBJECT
   
  public:
  	// MyGraphicsView( QWidget *pWnd );
  	MyGraphicsView();
  	~MyGraphicsView();
  
  	void setImg( QImage &img );
  
   private:
   	void paintEvent( QPaintEvent *event );
  
  	QImage m_img;
   };