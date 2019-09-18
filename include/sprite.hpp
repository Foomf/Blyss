#pragma once

#include <memory>
#include <string>
#include <cstdint>

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
    explicit sprite(std::shared_ptr<shader> shader, const std::shared_ptr<texture_cache>& texture_cache, const std::string& file_path, std::int32_t tx, std::int32_t ty);
    ~sprite();

    void draw() const;
};