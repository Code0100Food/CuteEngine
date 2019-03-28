#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <QWidget>

class BasicPrimitive;

class Viewport : public QWidget
{
    Q_OBJECT
public:

    explicit Viewport(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent* _event)override;

private:

    void PaintPrimitive(const BasicPrimitive* target); //No const because of QPaint instantiation

signals:

public slots:
};

#endif // VIEWPORT_H
