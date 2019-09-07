#include <iostream>
#include <cstdlib>
#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GlfwState.hpp"

using glfw_window_ptr = std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)>;

int main()
{
	const GlfwState glfw_state;

	if (!glfw_state.is_success())
	{
		return EXIT_FAILURE;
	}

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

	const glfw_window_ptr window(glfwCreateWindow(800, 600, "Thimble", nullptr, nullptr), glfwDestroyWindow);
	if(!window)
	{
		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window.get());

	if(!gladLoadGL())
	{
		return EXIT_FAILURE;
	}

    return EXIT_SUCCESS;
}
