#ifndef HIERARCHYWIDGET_H
#define HIERARCHYWIDGET_H

#include <QWidget>
#include "QListWidget"
#include "QPushButton"

class HierarchyWidget : public QWidget
{
    Q_OBJECT
public:
    HierarchyWidget(QWidget* parent = nullptr);
    ~HierarchyWidget();

private:
    int id = 0;

    void Start();

    QListWidget* widget_entity_list = nullptr;
    QPushButton* add_entity = nullptr;
    QPushButton* remove_entity = nullptr;

    void SetNewEntitySelected(std::string name);

public slots:

    void AddEntity();
    void RemoveEntity();
    void SelectedEntity();

public:

    QListWidgetItem* FindEntity(std::string entity_name);
    QList<QListWidgetItem*> GetSelectedItems() const;
};

#endif // HIERARCHYWIDGET_H
