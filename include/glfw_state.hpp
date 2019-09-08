#pragma once

class glfw_state
{
    bool is_success_;
    
public:
    glfw_state();
    ~glfw_state();

    glfw_state(const glfw_state&) = delete;
    glfw_state(glfw_state&&) = delete;
    glfw_state& operator=(const glfw_state&) = delete;
    glfw_state& operator=(glfw_state&&) = delete;

    bool is_success() const;
};