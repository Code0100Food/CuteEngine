#include "meshrenderewidget.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QGridLayout>
#include <QComboBox>
#include <QGridLayout>

MeshRendereWidget::MeshRendereWidget()
{
    //UI initialization
    QVBoxLayout* main_layout = new QVBoxLayout();

    QGridLayout* grid = new QGridLayout();

    //Window title
    QLabel* title = new QLabel("Mesh Renderer");
    main_layout->addWidget(title);

    select_mesh = new QLabel("Selected Mesh: No Selected");
    grid->addWidget(select_mesh, 0, 0);

    mesh_selector = new QComboBox();
    mesh_selector->addItem("No Mesh Selected");
    grid->addWidget(mesh_selector, 0, 1);

    main_layout->addLayout(grid);
    setLayout(main_layout);
}
