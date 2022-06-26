#ifndef FIELD_WIDGET_H
#define FIELD_WIDGET_H

#include "../models/battleship_game.h"
#include "widget_painter.h"
#include <QLabel>
#include <memory>

namespace battleshipGame {

/**
 * @brief The FieldWidget class is a custom widget for game field.
 */
class FieldWidget : public QWidget {

    Q_OBJECT

    class FieldPainter;

    const bool yours; /**< is fleet yours */

    /**
     * @param wx - horizontal coordinate.
     * @param wy - vertical coordinate.
     * @return Square in which located specified point in the widget.
     */
    Square getSquare(int wx, int wy);

public:
    static const int SIDE; /**< Size of the widget side. */

    /**
     * Constructor that creates yours field widget or
     * opponent field widget according to parameter yours.
     * @param yours - is fleet yours.
     */
    FieldWidget(bool yours);

    /**
     * Overrided destructor.
     */
    virtual ~FieldWidget() override;

    /**
     * Overrided method.
     * @return Size of the widget.
     */
    QSize sizeHint() const override;

    /**
     * Overrided method for handling paint event.
     */
    void paintEvent(QPaintEvent*) override;

    /**
     * Overrided method for hadling mouse move event.
     */
    void mouseMoveEvent(QMouseEvent*) override;

    /**
     * Overrided method for hadling mouse press event.
     */
    void mousePressEvent(QMouseEvent*) override;

    /**
     * Overrided method for hadling enter event.
     */
    void enterEvent(QEvent*) override;

    /**
     * Overrided method for hadling leave event.
     */
    void leaveEvent(QEvent*) override;

signals:
    /**
     * Signal that emits when player place a new ship to the fleet.
     */
    void shipsMapChanged();

    /**
     * Signal that emits when player fired a valid square.
     */
    void fired(FireResult fireResult);
};

}

#endif // FIELD_WIDGET_H
