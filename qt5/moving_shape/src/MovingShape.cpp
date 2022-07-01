// BadproG.com
#include "MovingShape.h"
#include <QPainter>
#include <QDebug>

// ============================================================================
// Constructor
// ============================================================================

/**
 * @brief MovingShape::MovingShape
 * @param parent
 */
MovingShape::MovingShape(QWidget *parent) : QWidget(parent) {
    setPointX(200);
    setPointY(100);
    setStep(10);
    setEllipseWidth(100);
    setEllipseHeight(100);
    setEllipsePen(5);
    setFocusPolicy(Qt::StrongFocus);
}

// ============================================================================
// Misc
// ============================================================================

/**
 * @brief MovingShape::move
 * @param choice
 */
void MovingShape::move(IMovable::Direction choice) {
    switch (choice) {
    case kDirectionDown:
        setPointY(getPointY() + getStep());
        qDebug() << "Down";
        QWidget::update();
        break;
    case kDirectionLeft:
        setPointX(getPointX() - getStep());
        qDebug() << "Left";
        QWidget::update();
        break;
    case kDirectionRight:
        setPointX(getPointX() + getStep());
        qDebug() << "Right";
        QWidget::update();
        break;
    case kDirectionUp:
        setPointY(getPointY() - getStep());
        qDebug() << "Up";
        QWidget::update();
        break;
    default:
        break;
    }
}

// ============================================================================
// Paint
// ============================================================================

/**
 * @brief MovingShape::paintEvent
 * @param event
 */
void MovingShape::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter;
    QRectF rectangle(getPointX(), getPointY(), getEllipseWidth(), getEllipseHeight());
    QPen pen_ellipse(Qt::black);

    pen_ellipse.setWidth(getEllipsePen());
    painter.begin(this);
    painter.setPen(pen_ellipse);
    painter.setBrush(Qt::cyan);
    painter.drawEllipse(rectangle);
    painter.end();
}

// ============================================================================
// Key
// ============================================================================

/**
 * @brief MovingShape::keyPressEvent
 * @param keyEvent
 */
void MovingShape::keyPressEvent(QKeyEvent *keyEvent)
{
    switch (keyEvent->key()) {
    case Qt::Key_Down:
        move(kDirectionDown);
        break;
    case Qt::Key_Left:
        move(kDirectionLeft);
        break;
    case Qt::Key_Right:
        move(kDirectionRight);
        break;
    case Qt::Key_Up:
        move(kDirectionUp);
        break;
    default:
        break;
    }
}

// ============================================================================
// Get & Set
// ============================================================================

/**
 * @brief MovingShape::getPointX
 * @return
 */
int MovingShape::getPointX() const
{
    return _pointX;
}

/**
 * @brief MovingShape::getPointY
 * @return
 */
int MovingShape::getPointY() const
{
    return _pointY;
}

/**
 * @brief MovingShape::setPointX
 * @param pointX
 */
void MovingShape::setPointX(int pointX)
{
    _pointX = pointX;
}

/**
 * @brief MovingShape::setPointY
 * @param pointY
 */
void MovingShape::setPointY(int pointY)
{
    _pointY = pointY;
}

/**
 * @brief MovingShape::getStep
 * @return
 */
int MovingShape::getStep() const
{
    return _step;
}

/**
 * @brief MovingShape::setStep
 * @param step
 */
void MovingShape::setStep(int step)
{
    _step = step;
}

/**
 * @brief MovingShape::setEllipseHeight
 * @param ellipseHeight
 */
void MovingShape::setEllipseHeight(int ellipseHeight)
{
    _ellipseHeight = ellipseHeight;
}

/**
 * @brief MovingShape::setEllipseWidth
 * @param ellipseWidth
 */
void MovingShape::setEllipseWidth(int ellipseWidth)
{
    _ellipseWidth = ellipseWidth;
}

/**
 * @brief MovingShape::getEllipseHeight
 * @return
 */
int MovingShape::getEllipseHeight() const
{
    return _ellipseHeight;
}

/**
 * @brief MovingShape::getEllipseWidth
 * @return
 */
int MovingShape::getEllipseWidth() const
{
    return _ellipseWidth;
}

/**
 * @brief MovingShape::getEllipsePen
 * @return
 */
int MovingShape::getEllipsePen() const
{
    return _ellipsePen;
}

/**
 * @brief MovingShape::setEllipsePen
 * @param ellipsePen
 */
void MovingShape::setEllipsePen(int ellipsePen)
{
    _ellipsePen = ellipsePen;
}
