#include "shader.hpp"

#include <sstream>
#include <fstream>

#include "shader_build_exception.hpp"

shader::shader(const std::string& shader_name, const std::string& frag_output)
    : shader_program_ { make_program() }
    , shader_name_ { shader_name }
{
    compile(frag_output);
}

GLuint shader::make_program() const
{
    return glCreateProgram();
}

shader::~shader()
{
    glDeleteProgram(shader_program_);
}

void shader::use() const
{
    glUseProgram(shader_program_);
}

GLint shader::get_uniform(const std::string& uniform_name) const
{
    return glGetUniformLocation(shader_program_, uniform_name.c_str());
}

GLuint shader::make_shader(GLenum shaderType) const
{
    std::stringstream shader_path_stream;
    shader_path_stream << "../shaders/" << shader_name_ << ".";

    switch (shaderType)
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

    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(shader, sizeof(infoLog), nullptr, infoLog);
        throw shader_build_exception("Failed to compile shader!", infoLog, shader_path);
    }

    return shader;
}

void shader::compile(const std::string& frag_output) const
{
    auto vert_shader = make_shader(GL_VERTEX_SHADER);
    auto frag_shader = make_shader(GL_FRAGMENT_SHADER);

    glAttachShader(shader_program_, vert_shader);
    glAttachShader(shader_program_, frag_shader);
    glBindFragDataLocation(shader_program_, 0, frag_output.c_str());
    glLinkProgram(shader_program_);
    int success;
    glGetProgramiv(shader_program_, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(shader_program_, sizeof(infoLog), nullptr, infoLog);
        throw shader_build_exception("Failed to link shader program!", infoLog, shader_name_);
    }

    glDeleteShader(vert_shader);
    glDeleteShader(frag_shader);
}

GLint shader::get_attrib_loc(const std::string& attr_name) const
{
    return glGetAttribLocation(shader_program_, attr_name.c_str());
}



