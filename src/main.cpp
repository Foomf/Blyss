#include <iostream>
#include <cstdlib>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GlfwState.hpp"

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
	
	const auto window = glfwCreateWindow(800, 600, "Thimble", nullptr, nullptr);
	if(!window)
	{
		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	if(!gladLoadGL())
	{
		glfwDestroyWindow(window);
		return EXIT_FAILURE;
	}

	glfwDestroyWindow(window);
    return EXIT_SUCCESS;
}
