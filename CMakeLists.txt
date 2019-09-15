cmake_minimum_required(VERSION 3.12)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(SHADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/shaders CACHE PATH "Shaders folder")

if(WIN32)
    set(HIDE_CONSOLE ON CACHE BOOL "")
endif()

set(PROG_NAME Thimble)
project (${PROG_NAME})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(IMGUI_DIR lib/imgui)
set(GLM_DIR lib/glm)
set(SPDLOG_DIR lib/spdlog)
set(STB_DIR lib/stb)

add_subdirectory(lib/glfw)

add_subdirectory(lib/gladimpl)

add_library(imgui
    ${IMGUI_DIR}/imconfig.h
    ${IMGUI_DIR}/imgui_internal.h
    ${IMGUI_DIR}/imgui.h
    ${IMGUI_DIR}/imstb_rectpack.h
    ${IMGUI_DIR}/imstb_textedit.h
    ${IMGUI_DIR}/imstb_truetype.h
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui.cpp
)

add_compile_definitions(IMGUI_IMPL_OPENGL_LOADER_GLAD)
add_compile_definitions(SHADER_DIR="${SHADER_DIR}")

set(HDR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

include_directories(${HDR_DIR})
include_directories(${IMGUI_DIR})
include_directories(${IMGUI_DIR}/examples)
include_directories(${GLM_DIR})
include_directories(${SPDLOG_DIR}/include)
include_directories(${STB_DIR})

set(SRCS
    ${IMGUI_DIR}/examples/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/examples/imgui_impl_opengl3.cpp
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/glfw_state.cpp
    ${SRC_DIR}/gl_exception.cpp
    ${SRC_DIR}/gl_error.cpp
    ${SRC_DIR}/shader_build_exception.cpp
    ${SRC_DIR}/shader.cpp
    ${SRC_DIR}/vertex_buffer_object.cpp
    ${SRC_DIR}/vertex_array_object.cpp
    ${SRC_DIR}/element_array_buffer.cpp
    ${SRC_DIR}/sprite.cpp
    ${SRC_DIR}/tile_grid.cpp
    ${SRC_DIR}/texture.cpp
    ${SRC_DIR}/texture_cache.cpp
)

set (HDRS
    ${IMGUI_DIR}/examples/imgui_impl_glfw.h
    ${IMGUI_DIR}/examples/imgui_impl_opengl3.h
    ${HDR_DIR}/glfw_state.hpp
    ${HDR_DIR}/gl_exception.hpp
    ${HDR_DIR}/gl_error.hpp
    ${HDR_DIR}/shader_build_exception.hpp
    ${HDR_DIR}/shader.hpp
    ${HDR_DIR}/vertex_buffer_object.hpp
    ${HDR_DIR}/vertex_array_object.hpp
    ${HDR_DIR}/element_array_buffer.hpp
    ${HDR_DIR}/sprite.hpp
    ${HDR_DIR}/tile_grid.hpp
    ${HDR_DIR}/texture.hpp
    ${HDR_DIR}/texture_cache.hpp
)

if(HIDE_CONSOLE)
add_compile_definitions(HIDE_CONSOLE)
add_executable(${PROG_NAME} WIN32 ${SRCS} ${HDRS})
else()
add_executable(${PROG_NAME} ${SRCS} ${HDRS})
endif()
target_link_libraries(${PROG_NAME} gladimpl)
target_link_libraries(${PROG_NAME} glfw)
target_link_libraries(${PROG_NAME} imgui)
