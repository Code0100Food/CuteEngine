#include "circlewidget.h"
#include <QPainter>
#include <iostream>

CircleWidget::CircleWidget(QWidget *aParent) : BasicPrimitive(PT_CIRCLE,aParent)
{
    setAutoFillBackground(true);
}

QSize CircleWidget::sizeHint() const
{
    return QSize(mRecommendedSize, mRecommendedSize);
}

QSize CircleWidget::minimumSizeHint() const
{
    return QSize(mRecommendedMinimumSize, mRecommendedMinimumSize);
}

void CircleWidget::paintEvent(QPaintEvent* aEvent)
{
    // Prepare the painter for this widget
    QPainter painter(this);

    QBrush Brush;
    QPen Pen;

    // Brush/Pen configuration
    Brush.setColor(GetColor());
    Brush.setStyle(Qt::BrushStyle::SolidPattern);
    Pen.setStyle(Qt::PenStyle::DashLine);
    painter.setBrush(Brush);
    painter.setPen(Pen);

    // Draw circle    
    QRect CircleRect(GetX(), GetY(), GetWidth(), GetHeight());
    painter.drawEllipse(CircleRect);
}
