#pragma once

#include <glad/glad.h>

#include <string>

namespace gl_err
{
    void post_call_callback(const char* name, void* funcptr, int len_args, ...);

    std::string to_string(GLenum error);
}