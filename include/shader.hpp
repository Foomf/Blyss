#pragma once

#include <string>
#include <glad/glad.h>

class shader
{
    GLuint shader_program_;
    std::string shader_name_;

    GLuint make_shader(GLenum shader_type) const;
    GLuint make_program() const;

public:
    shader(const std::string& shader_name, const std::string& frag_output);
    ~shader();

    shader(const shader&) = delete;
    shader(shader&&) = delete;
    shader& operator=(const shader&) = delete;
    shader& operator=(shader&&) = delete;

    void compile(const std::string& frag_output) const;
    void use() const;
    GLint get_uniform(const std::string& uniform_name) const;
    GLint get_attrib_loc(const std::string& attr_name) const;
};