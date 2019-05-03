#ifndef INSPECTOR_H
#define INSPECTOR_H

#include <QWidget>

class QVBoxLayout;
class QTextEdit;
class QComboBox;
class TransformWidget;
class Entity;
class MeshRendereWidget;
class QPushButton;

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

    void AddMeshToWidget(const char* name);
    void AddMaterialToWidget(const char* name);

private:

    QVBoxLayout* layout = nullptr;
    QTextEdit* name_display = nullptr;
    QComboBox* add_component_button = nullptr;

    QPushButton* add_mesh_renderer = nullptr;
    QPushButton* add_light_source = nullptr;

    TransformWidget* transform_widget = nullptr;
    MeshRendereWidget* mesh_renderer_widget = nullptr;

public slots:

    void AddComponent();
    void CreateTransformation();
    void CreateMeshRenderer();
    void CreateBasicPrimitive();
    void Rename();

    void AddMeshRenderer();

};

#endif // INSPECTOR_H
