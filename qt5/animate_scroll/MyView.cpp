/**
 * MyView.cpp
 * 2022-06-01 K.OHWADA
 */

// reference : https://stackoverflow.com/questions/35056987/programmatic-scrolling-with-qgraphicsview-and-qgraphicsitem

#include <stdio.h>
#include <QTimer>
#include "MyView.h"

/**
 * constractor
 */
// warning: unused parameter 'pScene'
MyView::MyView(QGraphicsScene* pScene) : QGraphicsView(pScene, NULL)
{
    // none
}


/**
 * AnimateBy
 */
void MyView::AnimateBy(int x)
{
    const float UPDATE_FREQ = (1000/30.0); // ~30 frames per second

    QPointF currScenePos = sceneRect().center();

    int curX = currScenePos.x();
    int endPos = curX + x;

    int distanceToAnimate = (endPos - curX);

        // speed = dist / time
    float updatePosInterval = (float)distanceToAnimate / UPDATE_FREQ;

    printf("updatePosInterval: %f \n", updatePosInterval);

    static float newXPos = sceneRect().center().x();

    QTimer* pTimer = new QTimer;

    QObject::connect(pTimer, &QTimer::timeout, [=](){

        newXPos += updatePosInterval;
        centerOn(newXPos, sceneRect().center().y());   

            // check for end position or time, then....
        if(newXPos >= endPos)
        {
                pTimer->stop();
                pTimer->deleteLater();
        }
} );

    pTimer->start(UPDATE_FREQ);
}
