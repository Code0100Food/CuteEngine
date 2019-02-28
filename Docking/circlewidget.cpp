#include "circlewidget.h"
#include <QPainter>
#include <iostream>

CircleWidget::CircleWidget(QWidget *aParent) : mRadius(64), mColor(QColor::fromRgb(127, 190, 220)), QWidget(aParent)
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

bool CircleWidget::SetRadius(uint aRadius)
{
    bool RetValue = true;
    mRadius = aRadius;
    if (mRadius < mRecommendedMinimumSize)
    {
        std::cout << "Circle size below recommended!!" << std::endl;
        RetValue = false;
    }
    return RetValue;
}

const uint CircleWidget::GetRadius() const
{
    return mRadius;
}

void CircleWidget::SetColor(QColor aColor)
{
    mColor = aColor;
}

const QColor CircleWidget::GetColor() const
{
    return mColor;
}

void CircleWidget::paintEvent(QPaintEvent* aEvent)
{
    // Prepare the painter for this widget
    QPainter painter(this);

    QBrush Brush;
    QPen Pen;

    // Brush/Pen configuration
    Brush.setColor(mColor);
    Brush.setStyle(Qt::BrushStyle::SolidPattern);
    Pen.setStyle(Qt::PenStyle::DashLine);
    painter.setBrush(Brush);
    painter.setPen(Pen);

    // Draw circle
    int r = mRadius;
    int w = r * 2;
    int h = r * 2;
    int x = rect().width()/ 2 - r;
    int y = rect().height()/ 2 - r;
    QRect CircleRect(x, y, w, h);
    painter.drawEllipse(CircleRect);
}
