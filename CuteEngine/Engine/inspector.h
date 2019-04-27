#ifndef INSPECTOR_H
#define INSPECTOR_H

#include <QWidget>

class QVBoxLayout;
class QTextEdit;
class QComboBox;
class TransformWidget;
class Entity;

class Inspector : public QWidget
{
Q_OBJECT
public:

    Inspector(QWidget* parent = nullptr);
    ~Inspector();

public:

    void Start();
    void SetName(QString entity_name);

    void UIReadEntity(Entity* selected_entity);

    void ShowUI();
    void HideUI();

    QVBoxLayout* GetLayout() const {return layout;}

private:

    QVBoxLayout* layout = nullptr;
    QTextEdit* name_display = nullptr;
    QComboBox* add_component_button = nullptr;
    TransformWidget* transform_widget = nullptr;

public slots:

    void AddComponent();
    void CreateTransformation();
    void CreateMeshRenderer();
    void CreateBasicPrimitive();
    void Rename();

};

#endif // INSPECTOR_H
