#include "gl_exception.hpp"

namespace gl_err
{
    gl_exception::gl_exception(const std::string& message)
        : std::runtime_error(message)
    {
    }
}