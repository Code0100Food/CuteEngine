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

    QLabel* select_mesh = nullptr;
    QComboBox* mesh_selector = nullptr;
};

#endif // MESHRENDEREWIDGET_H
