#include "element_array_buffer.hpp"

element_array_buffer::element_array_buffer(const std::vector<std::uint16_t>& vertices, const GLenum usage)
    : eab_ { make_eab() }
    , size_ { vertices.size() }
{
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(std::uint16_t)* vertices.size(), vertices.data(), usage);
}

element_array_buffer::~element_array_buffer()
{
    glDeleteBuffers(1, &eab_);
}

GLuint element_array_buffer::make_eab()
{
    GLuint eab;
    glGenBuffers(1, &eab);
    return eab;
}

void element_array_buffer::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eab_);
}

size_t element_array_buffer::get_size() const
{
    return size_;
}




