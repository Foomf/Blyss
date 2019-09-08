#include "shader_build_exception.hpp"

#include <sstream>

shader_build_exception::shader_build_exception(const std::string& error_message, const std::string& gl_compile_error, const std::string& file_name)
    : std::exception { make_message(file_name, error_message).c_str() }
    , error_message_ { gl_compile_error }
{
}

shader_build_exception::shader_build_exception(const std::string& error_message, const std::string& gl_compile_error)
    : std::exception { error_message.c_str() }
    , error_message_ { gl_compile_error }
{
}

shader_build_exception::shader_build_exception(const std::string& error_message)
    : std::exception { error_message.c_str() }
    , error_message_ { "" }
{
}

std::string shader_build_exception::make_message(const std::string& file_name, const std::string& error_message)
{
    std::stringstream ss;
    ss << "[" << file_name << "]: " << error_message;
    return ss.str();
}

const std::string& shader_build_exception::get_compile_error_message() const
{
    return error_message_;
}
