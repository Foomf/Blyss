#include "texture_cache.hpp"

std::shared_ptr<texture> texture_cache::get_texture(const std::string& file_name)
{
    const auto search = textures_.find(file_name);

    if (search == textures_.end())
    {
        return load_and_cache_texture(file_name);
    }

    if (auto t = search->second.lock())
    {
        return t;
    }

    return load_and_cache_texture(file_name);
}

std::shared_ptr<texture> texture_cache::load_and_cache_texture(const std::string& file_name)
{
    auto t = std::make_shared<texture>(file_name);
    textures_[file_name] = t;
    return t;
}

