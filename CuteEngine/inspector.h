#ifndef INSPECTOR_H
#define INSPECTOR_H

#include <QWidget>

class QVBoxLayout;
class QComboBox;

class Inspector : public QWidget
{
Q_OBJECT
public:

    Inspector(QWidget* parent = nullptr);
    ~Inspector();

    void Start();

private:

    QVBoxLayout* layout = nullptr;
    QComboBox* add_component_button = nullptr;

public slots:

    void AddComponent();
    void CreateTransformation();
    void CreateBasicPrimitive();

};

#endif // INSPECTOR_H
