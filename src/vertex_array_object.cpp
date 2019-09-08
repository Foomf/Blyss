#include "vertex_array_object.hpp"

vertex_array_object::vertex_array_object()
    : vao_ { make_vao() }
{
}

vertex_array_object::~vertex_array_object()
{
    glDeleteBuffers(1, &vao_);
}

GLuint vertex_array_object::make_vao()
{
    GLuint vao;
    glGenVertexArrays(1, &vao);
    return vao;
}

void vertex_array_object::bind() const
{
    glBindVertexArray(vao_);
}


