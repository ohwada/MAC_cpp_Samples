#ifndef WIDGET_PAINTER_H
#define WIDGET_PAINTER_H

#include <QWidget>
#include <QPainter>

/**
 *  @brief The WidgetPainter class is an interface for painting QWidgets.
 */
template <typename QWidgetType>
class WidgetPainter {

protected:
    QPainter* painter; /**< painter using for painting widget */

public:
    /**
     * Constructor that initializes QPainter from specified
     * QWidget, dynamically casted to QWidgetType.
     */
    WidgetPainter(QWidget* widget);

    /**
     * Destructor that deletes QPainter.
     */
    virtual ~WidgetPainter();

    /**
     * Paints widget using initialized QPainter.
     */
    virtual void paint() = 0;
};

#endif // WIDGET_PAINTER_H
