#pragma once

#include <cstdint>
#include <vector>
#include <memory>

#include <glad/glad.h>

#include "sprite.hpp"
#include "shader.hpp"
#include "texture_cache.hpp"

class tile_grid
{
    std::shared_ptr<texture_cache> texture_cache_;
    std::shared_ptr<shader> shader_;
    std::vector<std::unique_ptr<sprite>> sprites_;
    std::int32_t width_;
    std::int32_t height_;
    GLint model_uniform_;

    sprite* tile_at(std::int32_t x, std::int32_t y) const;

    std::int32_t get_index(std::int32_t x, std::int32_t y) const;

    void draw(std::int32_t x, std::int32_t y) const;

public:
    tile_grid(std::shared_ptr<shader> shader, std::int32_t width, std::int32_t height);
    ~tile_grid() = default;

    tile_grid(const tile_grid&) = delete;
    tile_grid(tile_grid&&) = delete;
    tile_grid& operator=(const tile_grid&) = delete;
    tile_grid& operator=(tile_grid&&) = delete;

    void set_tile(std::int32_t x, std::int32_t y);

    void draw() const;
};