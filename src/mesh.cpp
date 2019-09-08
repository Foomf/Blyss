#include "mesh.hpp"

mesh::mesh(const std::vector<float>& vertices, std::uint32_t stride, const std::vector<std::uint16_t>& indices, GLuint usage)
    : vao_ { std::make_unique<vertex_array_object>() }
    , vbo_ { std::make_unique<vertex_buffer_object>(vertices, stride, usage) }
    , eab_ { std::make_unique<element_array_buffer>(indices, usage) }
    , stride_ { stride }
{
}

mesh::mesh(const std::vector<float>& vertices, std::uint32_t stride, GLuint usage)
    : vao_{ std::make_unique<vertex_array_object>() }
    , vbo_{ std::make_unique<vertex_buffer_object>(vertices, stride, usage) }
    , eab_{ }
    , stride_{ stride }
{
    
}


void mesh::bind() const
{
    vao_->bind();
}

void mesh::config_attribute(GLuint location, GLint size, GLuint offset) const
{
    bind();
    glEnableVertexAttribArray(location);
    glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE, stride_ * sizeof(float), (void*)(offset * sizeof(float)));
}

void mesh::draw() const
{
    bind();
    if (eab_)
    {
        glDrawElements(GL_TRIANGLES, eab_->get_size(), GL_UNSIGNED_SHORT, (GLvoid*)0);
    }
    else
    {
        glDrawArrays(GL_TRIANGLES, 0, vbo_->size());
    }
}
