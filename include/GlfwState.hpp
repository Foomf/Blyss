#pragma once

class GlfwState
{
	bool _is_success;
	
public:
	GlfwState();
	~GlfwState();

	GlfwState(const GlfwState&) = delete;
	GlfwState(GlfwState&&) = delete;
	GlfwState& operator=(const GlfwState&) = delete;
	GlfwState& operator=(GlfwState&&) = delete;

	bool is_success() const;
};