// BadproG.com
#ifndef MOVING_SHAPE_1_MOVINGSHAPE_H_
#define MOVING_SHAPE_1_MOVINGSHAPE_H_

#include <QObject>
#include "IMovable.h"
#include <QWidget>
#include <QKeyEvent>

class MovingShape : public QWidget, public IMovable
{
    Q_OBJECT
public:
    explicit MovingShape(QWidget *parent = 0);

    // Misc
    void move(Direction);
    // Get & Set
    int getPointX() const;
    int getPointY() const;
    void setPointX(int pointX);
    void setPointY(int pointY);
    int getStep() const;
    void setStep(int step);
    int getEllipseWidth() const;
    int getEllipseHeight() const;
    void setEllipseWidth(int ellipseWidth);
    void setEllipseHeight(int ellipseHeight);
    void setEllipsePen(int ellipsePen);
    int getEllipsePen() const;

protected:
    void keyPressEvent(QKeyEvent *keyEvent);
    void paintEvent(QPaintEvent *event);

private:
    int _pointX;
    int _pointY;
    int _step;
    int _ellipseWidth;
    int _ellipseHeight;
    int _ellipsePen;

signals:

public slots:

};

#endif // MOVING_SHAPE_1_MOVINGSHAPE_H
