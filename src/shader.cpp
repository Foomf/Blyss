#include "shader.hpp"

#include <sstream>
#include <fstream>
#include <utility>

#include "shader_build_exception.hpp"

shader::shader(std::string shader_name, const std::string& frag_output)
    : shader_program_ { make_program() }
    , shader_name_ {std::move(shader_name)}
{
    compile(frag_output);
}

shader::~shader()
{
    glDeleteProgram(shader_program_);
}

GLuint shader::make_program()
{
    return glCreateProgram();
}

void shader::use() const
{
    glUseProgram(shader_program_);
}

GLint shader::get_uniform(const std::string& uniform_name) const
{
    return glGetUniformLocation(shader_program_, uniform_name.c_str());
}

GLuint shader::make_shader(GLenum shader_type) const
{
    std::stringstream shader_path_stream;
    shader_path_stream << "../shaders/" << shader_name_ << ".";

    switch (shader_type)
    {
    case GL_VERTEX_SHADER:
        shader_path_stream << "vert";
        break;
    case GL_FRAGMENT_SHADER:
        shader_path_stream << "frag";
        break;
    default:
        throw shader_build_exception("Unrecognized shader typer!");
    }
    auto shader_path = shader_path_stream.str();
    std::ifstream stream{ shader_path };
    if (!stream.good())
    {
        throw shader_build_exception("Failed to open file!", "", shader_path);
    }

    std::stringstream buffer;
    buffer << stream.rdbuf();
    auto str = buffer.str();
    auto source = str.c_str();

    auto shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char info_log[512];
        glGetShaderInfoLog(shader, sizeof(info_log), nullptr, info_log);
        throw shader_build_exception("Failed to compile shader!", info_log, shader_path);
    }

    return shader;
}

void shader::compile(const std::string& frag_output) const
{
    const auto vert_shader = make_shader(GL_VERTEX_SHADER);
    const auto frag_shader = make_shader(GL_FRAGMENT_SHADER);

    glAttachShader(shader_program_, vert_shader);
    glAttachShader(shader_program_, frag_shader);
    glBindFragDataLocation(shader_program_, 0, frag_output.c_str());
    glLinkProgram(shader_program_);
    int success;
    glGetProgramiv(shader_program_, GL_LINK_STATUS, &success);
    if (!success)
    {
        char info_log[512];
        glGetProgramInfoLog(shader_program_, sizeof(info_log), nullptr, info_log);
        throw shader_build_exception("Failed to link shader program!", info_log, shader_name_);
    }

    glDeleteShader(vert_shader);
    glDeleteShader(frag_shader);
}

GLint shader::get_attrib_loc(const std::string& attr_name) const
{
    return glGetAttribLocation(shader_program_, attr_name.c_str());
}
