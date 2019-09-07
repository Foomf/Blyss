#pragma once

#include <string>
#include <glad/glad.h>

namespace gl_err
{

    void check_gl_state();

    std::string to_string(GLenum error);

#ifdef NDEBUG
#define GL_CHECK()
#else
#define GL_CHECK() gl_err::check_gl_state()
#endif
}