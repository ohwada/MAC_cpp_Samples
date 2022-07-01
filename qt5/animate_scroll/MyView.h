#pragma once
/**
 * MyView.h
 * 2022-06-01 K.OHWADA
 */

#include <QGraphicsScene>
#include <QGraphicsView>


/**
 * class MyView
 */
class MyView : public QGraphicsView
{
public:
    MyView(QGraphicsScene* pScene);
    void AnimateBy(int x);

private:
};
