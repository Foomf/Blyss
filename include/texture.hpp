#pragma once

#include <string>

#include <glad/glad.h>

class texture
{
    GLuint gl_texture_id_ = 0;

public:
    texture(const std::string& file_path);
    ~texture();

    texture(const texture&) = delete;
    texture(texture&&) = delete;
    texture& operator=(const texture&) = delete;
    texture& operator=(texture&&) = delete;

    void use() const;
};