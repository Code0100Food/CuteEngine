#ifndef INSPECTOR_H
#define INSPECTOR_H

#include <QWidget>

class QVBoxLayout;
class QTextEdit;
class QComboBox;
class TransformWidget;
class Entity;
class MeshRendereWidget;
class QCheckBox;
class QPushButton;
class LightWidget;

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

    QCheckBox* show_grid_checkbox = nullptr;
    QCheckBox* show_bloom_checkbox = nullptr;

    QPushButton* add_mesh_renderer = nullptr;
    QPushButton* add_light_source = nullptr;

    TransformWidget* transform_widget = nullptr;
    MeshRendereWidget* mesh_renderer_widget = nullptr;
    LightWidget* light_settings_widget = nullptr;

public slots:

    void AddComponent();
    void CreateTransformation();
    void CreateMeshRenderer();
    void CreateBasicPrimitive();
    void Rename();

    void SetShowGrid(bool is_checked);
    void SetShowBloom(bool is_checked);

    void AddMeshRenderer();
    void AddLightComponent();

};

#endif // INSPECTOR_H

