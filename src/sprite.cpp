#include "sprite.hpp"
#include <utility>

#include <spdlog/spdlog.h>

#include "texture_ref.hpp"

sprite::sprite(std::shared_ptr<shader> shader, const std::shared_ptr<texture_cache>& texture_cache, const std::string& file_path, std::int32_t tx, std::int32_t ty)
    : texture_{texture_cache->get_texture(file_path)}
    , shader_{std::move(shader)}
{
    glGenVertexArrays(1, &vao_);
    glGenBuffers(1, &vbo_);
    glGenBuffers(1, &eab_);

    const auto t_ref = texture_->texture_at(tx, ty);

    float vertices[] = {
         0.5f,  0.5f,   t_ref.top_right.x, t_ref.top_right.y,
         0.5f, -0.5f,   t_ref.bottom_right.x, t_ref.bottom_right.y,
        -0.5f, -0.5f,   t_ref.bottom_left.x, t_ref.bottom_left.y,
        -0.5f,  0.5f,   t_ref.top_left.x, t_ref.top_left.y
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
