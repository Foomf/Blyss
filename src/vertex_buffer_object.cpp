#include "vertex_buffer_object.hpp"

vertex_buffer_object::vertex_buffer_object(const std::vector<float>& data, std::uint32_t stride, GLenum usage)
    : vbo_ { make_vbo() }
    , size_ { data.size() / stride }
{
    bind();
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), usage);
}

vertex_buffer_object::~vertex_buffer_object()
{
    glDeleteBuffers(1, &vbo_);
}

GLuint vertex_buffer_object::make_vbo()
{
    GLuint vbo;
    glGenBuffers(1, &vbo);
    return vbo;
}

std::uint32_t vertex_buffer_object::size() const
{
    return size_;
}

void vertex_buffer_object::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
}



