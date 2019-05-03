#ifndef MESHRENDEREWIDGET_H
#define MESHRENDEREWIDGET_H

#include <QWidget>

class QComboBox;
class QLabel;

class MeshRendereWidget : public QWidget
{
    Q_OBJECT
public:
    MeshRendereWidget();


    void AddMesh(const char* name);
    void AddMaterial(const char* name);

    void ResetComboBox(int type);
    void UpdateComboBox(int type, const char* name);

    //Debug
    QComboBox* texture_selector = nullptr;

private:
    QLabel* select_mesh = nullptr;
    QComboBox* mesh_selector = nullptr;



public slots:
    void SetSelectedMesh(int);
    void SetSelectedTexture(int);
};

#endif // MESHRENDEREWIDGET_H
