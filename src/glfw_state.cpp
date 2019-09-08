#include "glfw_state.hpp"

#include <GLFW/glfw3.h>

glfw_state::glfw_state()
{
    is_success_ = glfwInit();
}

glfw_state::~glfw_state()
{
    glfwTerminate();
}

bool glfw_state::is_success() const
{
    return is_success_;
}

