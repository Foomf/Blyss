#pragma once

#include <map>
#include <string>
#include <memory>

#include "texture.hpp"

class texture_cache
{
    std::map<std::string, std::weak_ptr<texture>> textures_;

    std::shared_ptr<texture> load_and_cache_texture(const std::string& file_name);

public:
    std::shared_ptr<texture> get_texture(const std::string& file_name);
};
