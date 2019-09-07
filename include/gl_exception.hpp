#pragma once
#include <stdexcept>
#include <string>

namespace gl_err
{
    class gl_exception final : public std::runtime_error
    {
    public:
        explicit gl_exception(const std::string& message);
    };
}