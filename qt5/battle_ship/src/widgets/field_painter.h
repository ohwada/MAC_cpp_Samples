#ifndef FIELD_PAINTER_H
#define FIELD_PAINTER_H

#include "field_widget.h"
#include "widget_painter.h"
#include "../models/ship.h"

using namespace std;

namespace battleshipGame {

/**
 * @brief The FieldWidget::FieldPainter class is used for painting FieldWidget.
 */
class FieldWidget::FieldPainter : public WidgetPainter<FieldWidget> {

    const int SQ = SIDE / 10; /**< size of square side. */
    const bool yours; /**< is fleet that drawing yours */
    const QColor FIELD_COLOR = QColor(80, 80, 80); /**< color of field grid */
    ///< color using for correct selected square
    const QColor CORRECT_COLOR = QColor(255, 255, 0);
    ///< color using for correct selected square
    const QColor INCORRECT_COLOR = QColor(255, 0, 0, 100);
    const QColor SHIP_COLOR = QColor(0, 0, 255); /**< color of ship */
    ///< color of ATTACKED and ATTACKED_WITH_SUCCESS symbols.
    const QColor ATTACK_COLOR = QColor(255, 0, 0);
// warning: private field 'NARROW_STROKE' is not used
    const int NARROW_STROKE = 2; /**< width of narrow stroke */
    const int THICK_STROKE = 4; /**< width of thick stroke */

    /**
     * Draws grid.
     */
    void drawField();

    /**
     * Draws fleet ships.
     */
    void drawFleet();

    /**
     * Draws square states.
     */
    void drawFleetState();

    /**
     * Draws specified ship in specified color,
     * @param ship - ship to draw.
     * @param color - color of the ship.
     */
    void drawShip(Ship ship, QColor color);

    /**
     * Draws specified square in specified color.
     * @param square - square to draw.
     * @param color - color of the square.
     */
    void drawSquare(Square square, QColor color);

    /**
     * Draws cross symbol for ATTACKED_WITH_SUCCESS squares.
     * @param square - square in which to draw cross.
     */
    void drawCross(Square square);

    /**
     * Draws small point symbol for ATTACKED squares.
     * @param square - square in which to draw small point symbol.
     */
    void drawSmallPoint(Square square);

    /**
     * @return Coordinates of left-top point of
     * specified square in the widget.
     */
    QPoint point(Square square);

    /**
     * Draws figures required in PLACING mode.
     */
    void drawPlacing();

    /**
     * Draws figures required in BATTLE mode.
     */
    void drawBattle();

public:
    /**
     * Constructor that calls base constructor.
     * @param fw - field widget to draw.
     */
    FieldPainter(FieldWidget* fw);

    /**
     * Overrided method for painting field widget.
     */
    void paint() override;
};

}

#endif // FIELD_PAINTER_H
