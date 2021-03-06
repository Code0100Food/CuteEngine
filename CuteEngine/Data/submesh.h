#ifndef SUBMESH_H
#define SUBMESH_H

#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLFunctions_3_3_Core>

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
            size += (num_components * sizeof(float));
        }
    }

   VertexFormat& operator=(const VertexFormat& other_vertex_format)
   {
       memcpy(attribute, other_vertex_format.attribute, sizeof(VertexAttribute) * MAX_VERTEX_ATTRIBUTES);
       size = other_vertex_format.size;

       return *this;
   }

    VertexAttribute attribute[MAX_VERTEX_ATTRIBUTES];
    int size = 0;
};

class Submesh
{
public:
    Submesh(VertexFormat format, void* data, int size);
    Submesh(VertexFormat format, void* _data, int size, void* _indexs, int index_size);
    ~Submesh() { }

    void ReLoad();
    void Draw();
    void Destroy();

VertexFormat vertex_format;

private:

    unsigned char* data = nullptr;
    size_t data_size = 0;

    unsigned int* indexs = nullptr;
    size_t indexs_count = 0;


    QOpenGLBuffer vertex_buffer_object;
    QOpenGLBuffer index_buffer_object;
    QOpenGLVertexArrayObject vertex_array_object;

};

#endif // SUBMESH_H
