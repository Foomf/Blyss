#include "tile_grid.hpp"

#include <stdexcept>
#include <utility>

#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp>

tile_grid::tile_grid(std::shared_ptr<shader> shader, std::int32_t width, std::int32_t height)
    : texture_cache_{std::make_shared<texture_cache>()}
    , shader_{std::move(shader)}
    , sprites_{width * height}
    , width_ {width}
    , height_ {height}
    , model_uniform_{shader_->get_uniform("model")}
{
    if(!shader_)
    {
        throw std::invalid_argument("shader");
    }
}

std::int32_t tile_grid::get_index(std::int32_t x, std::int32_t y) const
{
    if (x < 0 || y >= width_)
    {
        throw std::invalid_argument("x");
    }

    if (x < 0 || y >= height_)
    {
        throw std::invalid_argument("y");
    }

    return (x * height_) + y;;
}

sprite* tile_grid::tile_at(std::int32_t x, std::int32_t y) const
{
    const auto index = get_index(x, y);
    return sprites_[index].get();
}

void tile_grid::set_tile(std::int32_t x, std::int32_t y, const std::string& file_path)
{
    const auto index = get_index(x, y);
    sprites_[index] = std::make_unique<sprite>(shader_, texture_cache_, file_path);
}

void tile_grid::draw() const
{
    shader_->use();

    for (auto x = 0; x < height_; ++x)
    {
        for (auto y = 0; y < width_; ++y)
        {
            draw(x, y);
        }
    }
}

void tile_grid::draw(std::int32_t x, std::int32_t y) const
{
    const auto s = tile_at(x, y);
    if(!s)
    {
        return;
    }
    glm::mat4 model = glm::identity<glm::mat4>();
    glm::vec2 position(x * 100, y * 100);
    glm::vec2 size(100, 100);
    model = glm::translate(model, glm::vec3(position, 0.0f));
    model = glm::scale(model, glm::vec3(size, 1.0f));
    glUniformMatrix4fv(model_uniform_, 1, GL_FALSE, glm::value_ptr(model));
    s->draw();
}
