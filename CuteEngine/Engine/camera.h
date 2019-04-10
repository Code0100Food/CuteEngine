#ifndef CAMERA_H
#define CAMERA_H

#include <QVector3D>
#include <QMatrix4x4>

class Camera
{
public:
    Camera();

    QVector4D GetLeftRightBottomTop();

    QVector3D ScreenPointToWorldRay(int x, int y);
    QVector3D ScreenDisplacementToWorldVector(int x0, int y0, int x1, int y1);
    QVector2D WorldToScreenPoint(const QVector3D &p);

    void PrepareMatrices();

    int viewport_width = 128;
    int viewport_height = 128;

    float fov = 90.0f;
    float z_near = 0.1f;
    float z_far = 150.0f;

    float yaw = 0.0f;
    float pitch = 0.0f;
    QVector3D position;

    float speed = 0.5f;

    QMatrix4x4 world_matrix = QMatrix4x4(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1);
    QMatrix4x4 view_matrix =  QMatrix4x4(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1);
    QMatrix4x4 projection_matrix;

/*    QMatrix4x4* GetWorldMatrix(){return &world_matrix;}
    QMatrix4x4* GetViewMatrix(){return &view_matrix;}
    QMatrix4x4* GetProjectionMatrix(){return &projection_matrix;}

    void SetProjectionMatrix(QMatrix4x4 value) { projection_matrix = value; }*/

};

#endif // CAMERA_H
