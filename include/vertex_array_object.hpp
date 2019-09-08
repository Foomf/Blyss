#pragma once

#include <glad/glad.h>

class vertex_array_object
{
    const GLuint vao_;

    static GLuint make_vao();

public:
    vertex_array_object();
    ~vertex_array_object();

    vertex_array_object(const vertex_array_object&) = delete;
    vertex_array_object(vertex_array_object&&) = delete;
    vertex_array_object& operator=(const vertex_array_object&) = delete;
    vertex_array_object& operator=(vertex_array_object&&) = delete;

    void bind() const;
};