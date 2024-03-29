#include "gl_error.hpp"

#include <sstream>
#include <iostream>

#include <spdlog/spdlog.h>

#ifndef NDEBUG
#include "gl_exception.hpp"
#endif

namespace gl_err
{
    void post_call_callback(const char* name, void* funcptr, int len_args, ...)
    {
        auto error = glad_glGetError();
        if (error == GL_NO_ERROR)
        {
            return;
        }

        std::stringstream message;
        message << "Error: " << to_string(error);
        while (error = glad_glGetError(), error != GL_NO_ERROR)
        {
            message << to_string(error);
        }
        const auto text = message.str();
        const auto error_message = text.substr(0, text.size() - 2);
#ifdef NDEBUG
        spdlog::error("Error occurred in {}: {}", name, error_message);
#else
        throw gl_exception(error_message);
#endif
    }

    std::string to_string(const GLenum error)
    {
        switch (error)
        {
        case GL_NO_ERROR:
            return "None, ";
        case GL_INVALID_ENUM:
            return "Invalid enum, ";
        case GL_INVALID_VALUE:
            return "Invalid value, ";
        case GL_INVALID_OPERATION:
            return "Invalid operation, ";
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            return "Invalid framebuffer operation, ";
        case GL_OUT_OF_MEMORY:
            return "Out of memory, ";
        default:
            return "Unknown, ";
        }
    }
}
