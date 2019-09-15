#include "texture_cache.hpp"

std::shared_ptr<texture> texture_cache::get_texture(const std::string& file_name)
{
    if (textures_.find(file_name) == textures_.end())
    {
        auto t = std::make_shared<texture>(file_name);
        textures_[file_name] = t;;
        return t;
    }

    const auto weak_tex_ptr = textures_.at(file_name);
    if (auto t = weak_tex_ptr.lock())
    {
        return t;
    }
    else
    {
        t = std::make_shared<texture>(file_name);
        textures_[file_name] = t;;
        return t;
    }
}
