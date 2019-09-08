#pragma once

#include <cstdint>
#include <vector>

#include <glad/glad.h>

class element_array_buffer
{
    const GLuint eab_;
    const size_t size_;

    static GLuint make_eab();

public:
    element_array_buffer(const std::vector<std::uint16_t>& vertices, GLenum usage);
    ~element_array_buffer();

    void bind() const;
    size_t get_size() const;
};