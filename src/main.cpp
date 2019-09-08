#include <iostream>
#include <cstdlib>
#include <memory>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#endif

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui.h>

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "glfw_state.hpp"
#include "gl_error.hpp"
#include "shader_build_exception.hpp"
#include "shader.hpp"
#include "mat_fac.hpp"
#include "mesh.hpp"

using glfw_window_ptr = std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)>;

#ifdef _WIN32
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
#else
int main()
#endif
{
    const glfw_state glfw_state;

    if (!glfw_state.is_success())
    {
        return EXIT_FAILURE;
    }

#ifdef __APPLE__
    const auto glsl_version = "#version 150";
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#else
    const auto glsl_version = "#version 130";
#endif

    auto width = 800;
    auto height = 600;

    const glfw_window_ptr window(glfwCreateWindow(width, height, "Thimble", nullptr, nullptr), glfwDestroyWindow);
    if(!window)
    {
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window.get());
    glfwSwapInterval(1);

    if(!gladLoadGL())
    {
        return EXIT_FAILURE;
    }

#ifdef GLAD_DEBUG
    glad_set_post_callback(gl_err::post_call_callback);
#endif

    std::cout << "OpenGL Version " << GLVersion.major << "." << GLVersion.minor << " loaded.\n";

    //IMGUI_CHECKVERSION();
    //ImGui::CreateContext();
    //ImGui::StyleColorsDark();

    //ImGui_ImplGlfw_InitForOpenGL(window.get(), true);
    //ImGui_ImplOpenGL3_Init(glsl_version);

    const auto program = std::make_unique<shader>("shader", "FragColor");
    program->use();

    auto color_uniform = program->get_uniform("color");
    auto view_uniform = program->get_uniform("view");
    auto model_uniform = program->get_uniform("model");
    auto ortho_uniform = program->get_uniform("ortho");

    auto ortho = mat_fac::orthographic(-1.0f * (width / height), 1.0f * (width / height), -1, 1, -1, 1);

    //auto show_demo_window = true;
    const auto clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    auto view_x = 0.0f;
    auto view_y = 0.0f;

    auto identity = matrix<3>::identity();

    float color[3] = { 1.0, 0.0, 1.0 };

    std::vector<float> vertices = {
        -0.5f, -0.5F,
        0.5f, -0.5f,
        0.0f, 0.5f
    };

    auto m = std::make_unique<mesh>(vertices, 2, GL_STATIC_DRAW);

    auto pos_attr = program->get_attrib_loc("aPos");
    m->config_attribute(pos_attr, 2, 0);

    while(!glfwWindowShouldClose(window.get()))
    {
        glfwPollEvents();

        //ImGui_ImplOpenGL3_NewFrame();
        //ImGui_ImplGlfw_NewFrame();
        //ImGui::NewFrame();

        //if (show_demo_window)
        //    ImGui::ShowDemoWindow(&show_demo_window);

        //ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window.get(), &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);

        glUniformMatrix4fv(ortho_uniform, 1, GL_TRUE, ortho.get_ptr());

        auto view = mat_fac::translate(view_x, view_y);
        glUniformMatrix3fv(view_uniform, 1, GL_TRUE, view.get_ptr());

        glUniformMatrix3fv(model_uniform, 1, GL_TRUE, identity.get_ptr());

        glUniform3fv(color_uniform, 1, color);

        m->draw();

        //ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window.get());
    }

    //ImGui_ImplOpenGL3_Shutdown();
    //ImGui_ImplGlfw_Shutdown();
    //ImGui::DestroyContext();

    return EXIT_SUCCESS;
}
