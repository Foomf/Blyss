#pragma once

#include <memory>
#include <string>

#include <glad/glad.h>

#include "shader.hpp"
#include "texture.hpp"
#include "texture_cache.hpp"

class sprite
{
    GLuint vao_ = 0;
    GLuint vbo_ = 0;
    GLuint eab_ = 0;
    std::shared_ptr<texture> texture_;

    std::shared_ptr<shader> shader_;

public:
    explicit sprite(std::shared_ptr<shader> shader, std::shared_ptr<texture_cache> texture_cache, const std::string& file_path);
    ~sprite();

    void draw() const;
};