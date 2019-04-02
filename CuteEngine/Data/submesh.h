#ifndef SUBMESH_H
#define SUBMESH_H

#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

#define MAX_VERTEX_ATTRIBUTES 3

struct VertexAttribute
{
    bool enabled = false;
    int offset = 0;
    int num_components = 0;
};

class VertexFormat
{
public:

    void SetVertexAttribute(int location, int offset, int num_components)
    {
        if(location < MAX_VERTEX_ATTRIBUTES)
        {
            attribute[location].enabled = true;
            attribute[location].offset = offset;
            attribute[location].num_components = num_components;
        }
    }

    VertexAttribute attribute[MAX_VERTEX_ATTRIBUTES];
    int size = 0;
};

class Submesh
{
public:
    Submesh();

private:



};

#endif // SUBMESH_H
