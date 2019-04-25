#include "camera.h"

#include <qvector4d.h>
#include <qmath.h>
#include<iostream>

Camera::Camera(int width, int height)
{
    viewport_width = width;
    viewport_height = height;
}

QVector4D Camera::GetLeftRightBottomTop()
{
    const float aspectRatio = float(viewport_width/viewport_height);
    const float alpha = qDegreesToRadians(fov * 0.5f);
    const float top = z_near * qTan(alpha);
    const float bottom = -top;
    const float right = top * aspectRatio;
    const float left = -right;
    QVector4D params(left,right,bottom,top);
    return params;
}

QVector3D Camera::ScreenPointToWorldRay(int x, int y)
{
    QVector4D lrbt = GetLeftRightBottomTop();
    const float l = lrbt.x();
    const float r = lrbt.y();
    const float b = lrbt.z();
    const float t = lrbt.w();
    const float ray_x = l +(r-l) * x/ viewport_width;
    const float ray_y = b + (t - b) * (viewport_height - y - 1) / viewport_height;
    const float ray_z = -z_near;
    QVector3D ray_viewspace = QVector3D(ray_x,ray_y,ray_z);

    PrepareMatrices();

    QVector3D ray_world_space = QVector3D(world_matrix * QVector4D(ray_viewspace, 0.0f));

    return ray_world_space;
}

void Camera::PrepareMatrices()
{
    world_matrix.setToIdentity();
    world_matrix.translate(position);
    world_matrix.rotate(yaw, QVector3D(0.0f,1.0f,0.0f));
    world_matrix.rotate(pitch, QVector3D(1.0f,0.0f,0.0f));

    view_matrix = world_matrix.inverted();

    projection_matrix.setToIdentity();
    projection_matrix.perspective(fov,float(viewport_width)/viewport_height, z_near, z_far);
}
