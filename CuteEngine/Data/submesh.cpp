#include "submesh.h"
#include <iostream>
#include <QOpenGLFunctions>

Submesh::Submesh(VertexFormat format, void* _data, int size)
{
    vertex_format = format;
    data = (unsigned char*)_data;
    data_size = size * sizeof(float);
}

Submesh::Submesh(VertexFormat format, void* _data, int size, void* _indexs, int index_size) : vertex_buffer_object(QOpenGLBuffer::VertexBuffer), index_buffer_object(QOpenGLBuffer::IndexBuffer)
{
    vertex_format = format;

    data = new unsigned char[size];
    memcpy(data, _data, size);
    data_size = size;

    indexs = new unsigned int[index_size];
    memcpy(indexs, _indexs, index_size * sizeof(unsigned int));
    indexs_count = index_size;
}

void Submesh::ReLoad()
{
    QOpenGLFunctions* gl_functions = QOpenGLContext::currentContext()->functions();

    vertex_array_object.create();
    vertex_array_object.bind();

    if(data != nullptr)
    {
        vertex_buffer_object.create();
        vertex_buffer_object.bind();
        vertex_buffer_object.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
        vertex_buffer_object.allocate(data, int(data_size));
        delete[] data;
        data = nullptr;
    }

    if(indexs_count > 0)
    {
        index_buffer_object.create();
        index_buffer_object.bind();
        index_buffer_object.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
        index_buffer_object.allocate(indexs, int(indexs_count * sizeof(unsigned int)));
        delete[] indexs;
        indexs = nullptr;
    }

    for(int i = 0; i < MAX_VERTEX_ATTRIBUTES; i++)
    {
        VertexAttribute& attribute = vertex_format.attribute[i];

        if(attribute.enabled)
        {
            gl_functions->glEnableVertexAttribArray(GLuint(i));
            gl_functions->glVertexAttribPointer(GLuint(i), attribute.num_components, GL_FLOAT, GL_FALSE, vertex_format.size, (void*)(attribute.offset));
        }
    }

    vertex_array_object.release();
    vertex_buffer_object.release();
    if(index_buffer_object.isCreated())
        index_buffer_object.release();

}

void Submesh::Draw()
{
    int num_vertices = data_size / vertex_format.size;
    QOpenGLFunctions* gl_functions = QOpenGLContext::currentContext()->functions();

    vertex_array_object.bind();
    if(indexs_count > 0)
    {
        gl_functions->glDrawElements(GL_TRIANGLES, indexs_count, GL_UNSIGNED_INT, nullptr);
    }
    else{
        gl_functions->glDrawArrays(GL_TRIANGLES, 0, num_vertices);
    }
    vertex_array_object.release();
}

void Submesh::Destroy()
{
    if(vertex_buffer_object.isCreated()) vertex_buffer_object.destroy();
    if(index_buffer_object.isCreated()) index_buffer_object.destroy();
    if(vertex_array_object.isCreated()) vertex_array_object.destroy();
}
