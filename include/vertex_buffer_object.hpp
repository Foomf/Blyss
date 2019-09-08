#pragma once

#include <cstdint>
#include <vector>

#include <glad/glad.h>

class vertex_buffer_object
{
    const GLuint vbo_;
    const std::uint32_t size_;

    static GLuint make_vbo();

public:
    vertex_buffer_object(const std::vector<float>& data, std::uint32_t stride, GLenum usage);
    ~vertex_buffer_object();

    vertex_buffer_object(const vertex_buffer_object&) = delete;
    vertex_buffer_object(vertex_buffer_object&&) = delete;
    vertex_buffer_object& operator=(const vertex_buffer_object&) = delete;
    vertex_buffer_object& operator=(vertex_buffer_object&&) = delete;

    std::uint32_t size() const;
    void bind() const;
};