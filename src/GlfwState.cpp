#include "GlfwState.hpp"

#include <GLFW/glfw3.h>

GlfwState::GlfwState()
{
	_is_success = glfwInit();
}

GlfwState::~GlfwState()
{
	glfwTerminate();
}

bool GlfwState::is_success() const
{
	return _is_success;
}

