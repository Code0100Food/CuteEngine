#ifndef CIRCLEWIDGET_H
#define CIRCLEWIDGET_H

#include <QWidget>
#include "basicprimitive.h"

class CircleWidget : public QWidget, BasicPrimitive
{
    Q_OBJECT
public:
    explicit CircleWidget(QWidget *aParent = nullptr);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

signals:

public slots:

private:
    void paintEvent(QPaintEvent* aEvent) override;

    uint mRecommendedSize = 256;
    uint mRecommendedMinimumSize = 64;
};

#endif // CIRCLEWIDGET_H
