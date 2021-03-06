#include "meshrenderer.h"

#include <qt_application.h>
#include <mainwindow.h>
#include <resourcemanager.h>
#include "../Data/mesh.h"
#include "Data/material.h"
#include<iostream>

MeshRenderer::MeshRenderer() : Component()
{
    type = COMPONENT_TYPE::COMPONENT_MESHRENDERER;
}

void MeshRenderer::Update()
{

}

void MeshRenderer::Draw()
{
    if(current_mesh != nullptr)
    {   
        current_mesh->Draw(mesh_material);
    }
}
