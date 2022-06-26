#include "widget_painter.h"
#include "field_widget.h"

template <typename QWidgetType>
WidgetPainter<QWidgetType>::WidgetPainter(QWidget* widget) {
    this->painter = new QPainter(static_cast<QWidgetType*>(widget));
}

template <typename QWidgetType>
WidgetPainter<QWidgetType>::~WidgetPainter() {
    delete painter;
}

// explicit instantiation
template class WidgetPainter<battleshipGame::FieldWidget>;
