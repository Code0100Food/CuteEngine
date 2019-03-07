#ifndef INSPECTOR_H
#define INSPECTOR_H

#include <QWidget>

namespace Ui
{
class inspector;
}

class inspector : public QWidget
{
    Q_OBJECT

public:

    explicit inspector(QWidget *parent = 0);
    ~inspector();

private:

    Ui::inspector *ui = nullptr;

    void CreateTransformation();
    void CreateBasicPrimitive();

private slots:

    void on_AddComponentComboBox_currentIndexChanged(const QString &arg1);
};

#endif // INSPECTOR_H
