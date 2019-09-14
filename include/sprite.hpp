#pragma once

#include <vector>
#include <memory>

#include <glad/glad.h>

#include "shader.hpp"

class sprite
{
    GLuint vao_ = 0;
    GLuint vbo_ = 0;
    GLuint eab_ = 0;
    GLuint texture_ = 0;

    std::shared_ptr<shader> shader_;

public:
    explicit sprite(std::shared_ptr<shader> shader);
    ~sprite();

    void draw() const;
};