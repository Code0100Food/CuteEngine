#ifndef CIRCLEWIDGET_H
#define CIRCLEWIDGET_H

#include <QWidget>
#include "basicprimitive.h"

class CircleWidget : BasicPrimitive
{
    Q_OBJECT
public:

    explicit CircleWidget(QWidget *aParent = nullptr);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    void paintEvent(QPaintEvent* aEvent) override;

signals:

public slots:

private:


    uint mRecommendedSize = 256;
    uint mRecommendedMinimumSize = 64;
};

#endif // CIRCLEWIDGET_H
