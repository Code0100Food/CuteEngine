#ifndef CIRCLEWIDGET_H
#define CIRCLEWIDGET_H

#include <QWidget>
#include "entity.h"

class CircleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CircleWidget(QWidget *aParent = nullptr);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

    bool SetRadius(uint aRadius); // !Returns false if its below recommended, although it resizes it anyway
    const uint GetRadius() const;

    void SetColor(QColor aColor);
    const QColor GetColor() const;

signals:

public slots:

private:
    void paintEvent(QPaintEvent* aEvent) override;

    uint mRadius;
    QColor mColor;

    uint mRecommendedSize = 256;
    uint mRecommendedMinimumSize = 64;
};

#endif // CIRCLEWIDGET_H
