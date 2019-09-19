#include "texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <spdlog/spdlog.h>

texture::texture(const std::string& file_path)
    : t_map_{0, 0, 0}
{
    glGenTextures(1, &gl_texture_id_);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gl_texture_id_);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    int width, height, nrChannels;
    const auto data = stbi_load(file_path.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        t_map_ = texture_map{ 64, width, height };
    }
    else
    {
        spdlog::error("Failed to load image!");
    }
    stbi_image_free(data);
}

texture::~texture()
{
    glDeleteTextures(1, &gl_texture_id_);
}

void texture::use() const
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gl_texture_id_);
}

texture_ref texture::texture_at(std::int32_t x, std::int32_t y) const
{
    return t_map_.get_ref(x, y);
}
