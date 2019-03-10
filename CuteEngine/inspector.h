#ifndef INSPECTOR_H
#define INSPECTOR_H

#include <QWidget>

class QVBoxLayout;
class QTextEdit;
class QComboBox;

class Inspector : public QWidget
{
Q_OBJECT
public:

    Inspector(QWidget* parent = nullptr);
    ~Inspector();

public:

    void Start();
    void SetName(QString entity_name);

    void ShowUI();
    void HideUI();

private:

    QVBoxLayout* layout = nullptr;
    QTextEdit* name_display = nullptr;
    QComboBox* add_component_button = nullptr;

public slots:

    void AddComponent();
    void CreateTransformation();
    void CreateBasicPrimitive();
    void Rename();

};

#endif // INSPECTOR_H
