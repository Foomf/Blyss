#include <iostream>
#include <cstdlib>
#include <memory>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#endif

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>

#include <spdlog/spdlog.h>

#include <curses.h>

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "glfw_state.hpp"
#include "gl_error.hpp"
#include "shader_build_exception.hpp"
#include "shader.hpp"
#include "vertex_buffer_object.hpp"
#include "sprite.hpp"
#include "tile_grid.hpp"

using glfw_window_ptr = std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)>;

GLuint proj_uniform = 0;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    glm::mat4 projection = glm::ortho(0.0f, (float)width, (float)height, 0.0f, -1.0f, 1.0f);
    //glm::mat4 projection = glm::identity<glm::mat4>();
    glUniformMatrix4fv(proj_uniform, 1, GL_FALSE, glm::value_ptr(projection));
}

#if defined(_WIN32) && defined(HIDE_CONSOLE)
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
#else
int main()
#endif
{
    int ch;

    initscr();			/* Start curses mode 		*/
    raw();				/* Line buffering disabled	*/
    keypad(stdscr, TRUE);		/* We get F1, F2 etc..		*/
    noecho();			/* Don't echo() while we do getch */

    printw("Type any character to see it in bold\n");
    ch = getch();			/* If raw() hadn't been called
                     * we have to press enter before it
                     * gets to the program 		*/
    if (ch == KEY_F(1))		/* Without keypad enabled this will */
        printw("F1 Key pressed");/*  not get to us either	*/
                    /* Without noecho() some ugly escape
                     * charachters might have been printed
                     * on screen			*/
    else
    {
        printw("The pressed key is ");
        attron(A_BOLD);
        printw("%c", ch);
        attroff(A_BOLD);
    }
    refresh();			/* Print it on to the real screen */
    getch();			/* Wait for user input */
    endwin();			/* End curses mode		  */

//    const glfw_state glfw_state;
//
//    if (!glfw_state.is_success())
//    {
//        spdlog::critical("Could initialize glfw!");
//        return EXIT_FAILURE;
//    }
//
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//#ifdef __APPLE__
//    const auto glsl_version = "#version 150";
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//#else
//    const auto glsl_version = "#version 130";
//#endif
//
//    auto width = 800;
//    auto height = 600;
//
//    const glfw_window_ptr window(glfwCreateWindow(width, height, "Thimble", nullptr, nullptr), glfwDestroyWindow);
//    if(!window)
//    {
//        spdlog::critical("Could not create glfw window!");
//        return EXIT_FAILURE;
//    }
//
//    glfwMakeContextCurrent(window.get());
//    glfwSetFramebufferSizeCallback(window.get(), framebuffer_size_callback);
//
//    glfwSwapInterval(1);
//    spdlog::info("V-sync is enabled.");
//
//    if(!gladLoadGL())
//    {
//        spdlog::critical("Could not load OpenGL!");
//        return EXIT_FAILURE;
//    }
//
//#ifdef GLAD_DEBUG
//    glad_set_post_callback(gl_err::post_call_callback);
//#endif
//
//    spdlog::info("OpenGL Version {}.{} loaded.", GLVersion.major, GLVersion.minor);
//
//    glViewport(0, 0, width, height);
//
//    std::vector<float> vertices = {
//        -0.5f, -0.5f, 0.0f,
//        0.5f, -0.5f, 0.0f,
//        0.0f, 0.5f, 0.0f
//    };
//
//    //IMGUI_CHECKVERSION();
//    //ImGui::CreateContext();
//    //ImGui::StyleColorsDark();
//
//    //ImGui_ImplGlfw_InitForOpenGL(window.get(), true);
//    //ImGui_ImplOpenGL3_Init(glsl_version);
//
//    const auto program = std::make_shared<shader>("shader", "FragColor");
//    program->use();
//
//    proj_uniform = program->get_uniform("projection");
//    auto view_uniform = program->get_uniform("view");
//    auto model_uniform = program->get_uniform("model");
//
//    glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
//    //glm::mat4 projection = glm::identity<glm::mat4>();
//    glUniformMatrix4fv(proj_uniform, 1, GL_FALSE, glm::value_ptr(projection));
//
//    glm::mat4 view = glm::identity<glm::mat4>();
//    view = glm::translate(view, glm::vec3(300, 300, 0));
//    glUniformMatrix4fv(view_uniform, 1, GL_FALSE, glm::value_ptr(view));
//
//    tile_grid grid(program, 2, 2);
//    grid.set_tile(0, 0, "spritesheet.png", 1, 0);
//    grid.set_tile(0, 1, "face2.png", 0, 0);
//    grid.set_tile(1, 0, "face3.png", 0, 0);
//    grid.set_tile(1, 1, "face4.png", 0, 0);
//
//    //glm::mat4 model = glm::identity<glm::mat4>();
//    //glm::vec2 position(200, 200);
//    //glm::vec2 size(300, 300);
//    //model = glm::translate(model, glm::vec3(position, 0.0f));
//    //model = glm::scale(model, glm::vec3(size, 1.0f));
//    //glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(model));
//
//    //auto s = sprite(program);
//
//
//    //auto show_demo_window = true;
//    const auto clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
//
//    while(!glfwWindowShouldClose(window.get()))
//    {
//        glfwPollEvents();
//
//        if (glfwGetKey(window.get(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
//        {
//            glfwSetWindowShouldClose(window.get(), true);
//        }
//
//        //ImGui_ImplOpenGL3_NewFrame();
//        //ImGui_ImplGlfw_NewFrame();
//        //ImGui::NewFrame();
//
//        //if (show_demo_window)
//        //    ImGui::ShowDemoWindow(&show_demo_window);
//
//        //ImGui::Render();
//        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        //s.draw();
//        grid.draw();
//
//        //ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
//
//        glfwSwapBuffers(window.get());
//    }
//
//    //ImGui_ImplOpenGL3_Shutdown();
//    //ImGui_ImplGlfw_Shutdown();
//    //ImGui::DestroyContext();

    return EXIT_SUCCESS;
}
