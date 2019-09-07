#include <iostream>
#include <cstdlib>
#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui.h>

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "GlfwState.hpp"
#include "gl_error.hpp"

using glfw_window_ptr = std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)>;

int main()
{
    const GlfwState glfw_state;

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

    const glfw_window_ptr window(glfwCreateWindow(800, 600, "Thimble", nullptr, nullptr), glfwDestroyWindow);
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

    std::cout << "OpenGL Version " << GLVersion.major << "." << GLVersion.minor << " loaded.\n";

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window.get(), true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    while(!glfwWindowShouldClose(window.get()))
    {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)& clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }



        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window.get(), &display_w, &display_h);
        glViewport(0, 0, display_w, display_h); GL_CHECK();
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w); GL_CHECK();
        glClear(GL_COLOR_BUFFER_BIT); GL_CHECK();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); GL_CHECK();

        glfwSwapBuffers(window.get());
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    return EXIT_SUCCESS;
}
