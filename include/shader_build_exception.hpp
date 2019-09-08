#pragma once

#include <exception>
#include <string>

class shader_build_exception final : public std::exception
{
    std::string error_message_;

    static std::string make_message(const std::string& file_name, const std::string& error_message);

public:
    shader_build_exception(const std::string& error_message, const std::string& gl_compile_error, const std::string& file_name);
    shader_build_exception(const std::string& error_message, const std::string& gl_compile_error);
    explicit shader_build_exception(const std::string& error_message);

    const std::string& get_compile_error_message() const;
};