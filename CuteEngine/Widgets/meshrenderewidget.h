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
    void ResetComboBox();
    void UpdateComboBox(const char* name);

private:
    QLabel* select_mesh = nullptr;
    QComboBox* mesh_selector = nullptr;

public slots:
    void SetSelectedMesh(int) const;
};

#endif // MESHRENDEREWIDGET_H
