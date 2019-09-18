#pragma once

#include <string>
#include <cstdint>

#include <glad/glad.h>

#include "texture_map.hpp"
#include "texture_ref.hpp"

class texture
{
    GLuint gl_texture_id_ = 0;
    texture_map t_map_;

public:
    texture(const std::string& file_path);
    ~texture();

    texture(const texture&) = delete;
    texture(texture&&) = delete;
    texture& operator=(const texture&) = delete;
    texture& operator=(texture&&) = delete;

    void use() const;

    texture_ref texture_at(std::int32_t x, std::int32_t y) const;
};