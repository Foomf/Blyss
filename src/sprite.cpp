#include "sprite.hpp"
#include <utility>

#include <spdlog/spdlog.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

sprite::sprite(std::shared_ptr<shader> shader)
    : texture_{std::make_unique<texture>("face.png")}
    , shader_{std::move(shader)}
{
    glGenVertexArrays(1, &vao_);
    glGenBuffers(1, &vbo_);
    glGenBuffers(1, &eab_);

    float vertices[] = {
         0.5f,  0.5f,   1.0f, 1.0f, // top right
         0.5f, -0.5f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f,   0.0f, 1.0f  // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    glBindVertexArray(vao_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    auto aPosAttrib = shader_->get_attrib_loc("aPos");
    glVertexAttribPointer(aPosAttrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(aPosAttrib);
    auto aTextCoordAttrib = shader_->get_attrib_loc("aTexCoord");
    glVertexAttribPointer(aTextCoordAttrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(aTextCoordAttrib);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eab_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

sprite::~sprite()
{
    glDeleteBuffers(1, &eab_);
    glDeleteBuffers(1, &vbo_);
    glDeleteVertexArrays(1, &vao_);
}

void sprite::draw() const
{
    shader_->use();
    glBindVertexArray(vao_);
    texture_->use();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
