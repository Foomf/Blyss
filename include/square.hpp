#pragma once

#include <vector>
#include <memory>

#include <glad/glad.h>

#include "shader.hpp"

class square
{
    GLuint vao_ = 0;
    GLuint vbo_ = 0;
    GLuint eab_ = 0;
    GLuint texture_ = 0;

    std::shared_ptr<shader> shader_;

public:
    explicit square(std::shared_ptr<shader> shader);
    ~square();

    void draw() const;
};