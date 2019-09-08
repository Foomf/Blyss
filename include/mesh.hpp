#pragma once

#include <memory>
#include <vector>
#include <cstdint>

#include <glad/glad.h>

#include "element_array_buffer.hpp"
#include "vertex_array_object.hpp"
#include "vertex_buffer_object.hpp"

class mesh
{
    const std::unique_ptr<vertex_array_object> vao_;
    const std::unique_ptr<vertex_buffer_object> vbo_;
    const std::unique_ptr<element_array_buffer> eab_;

    const std::uint32_t stride_;

public:
    mesh(const std::vector<float>& vertices, std::uint32_t stride, const std::vector<std::uint16_t>& indices, GLuint usage);
    mesh(const std::vector<float>& vertices, std::uint32_t stride, GLuint usage);

    mesh(const mesh&) = delete;
    mesh(mesh&&) = delete;
    mesh& operator=(const mesh&) = delete;
    mesh& operator=(mesh&&) = delete;

    void bind() const;
    void config_attribute(GLuint location, GLint size, GLuint offset) const;
    void draw() const;
};