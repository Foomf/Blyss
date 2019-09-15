#pragma once

#include <map>
#include <string>
#include <memory>

#include "texture.hpp"

class texture_cache
{
    std::map<std::string, std::weak_ptr<texture>> textures_;

public:
    std::shared_ptr<texture> get_texture(const std::string& file_name);
};
