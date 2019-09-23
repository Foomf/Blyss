cmake_minimum_required(VERSION 3.12)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(SHADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/shaders CACHE PATH "Shaders folder")

if(WIN32)
    set(HIDE_CONSOLE ON CACHE BOOL "")
endif()

set(PROG_NAME Blyss)
project (${PROG_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(IMGUI_DIR lib/imgui)
set(GLM_DIR lib/glm)
set(SPDLOG_DIR lib/spdlog)
set(STB_DIR lib/stb)
set(CURSES_DIR lib/PDCurses)

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

set(PDCURSES_SRCS
    ${CURSES_DIR}/pdcurses/addch.c
    ${CURSES_DIR}/pdcurses/addchstr.c
    ${CURSES_DIR}/pdcurses/addstr.c
    ${CURSES_DIR}/pdcurses/attr.c
    ${CURSES_DIR}/pdcurses/beep.c
    ${CURSES_DIR}/pdcurses/bkgd.c
    ${CURSES_DIR}/pdcurses/border.c
    ${CURSES_DIR}/pdcurses/clear.c
    ${CURSES_DIR}/pdcurses/color.c
    ${CURSES_DIR}/pdcurses/debug.c
    ${CURSES_DIR}/pdcurses/delch.c
    ${CURSES_DIR}/pdcurses/deleteln.c
    ${CURSES_DIR}/pdcurses/getch.c
    ${CURSES_DIR}/pdcurses/getstr.c
    ${CURSES_DIR}/pdcurses/getyx.c
    ${CURSES_DIR}/pdcurses/inch.c
    ${CURSES_DIR}/pdcurses/inchstr.c
    ${CURSES_DIR}/pdcurses/initscr.c
    ${CURSES_DIR}/pdcurses/inopts.c
    ${CURSES_DIR}/pdcurses/insch.c
    ${CURSES_DIR}/pdcurses/insstr.c
    ${CURSES_DIR}/pdcurses/instr.c
    ${CURSES_DIR}/pdcurses/kernel.c
    ${CURSES_DIR}/pdcurses/keyname.c
    ${CURSES_DIR}/pdcurses/mouse.c
    ${CURSES_DIR}/pdcurses/move.c
    ${CURSES_DIR}/pdcurses/outopts.c
    ${CURSES_DIR}/pdcurses/overlay.c
    ${CURSES_DIR}/pdcurses/pad.c
    ${CURSES_DIR}/pdcurses/panel.c
    ${CURSES_DIR}/pdcurses/printw.c
    ${CURSES_DIR}/pdcurses/refresh.c
    ${CURSES_DIR}/pdcurses/scanw.c
    ${CURSES_DIR}/pdcurses/scr_dump.c
    ${CURSES_DIR}/pdcurses/scroll.c
    ${CURSES_DIR}/pdcurses/slk.c
    ${CURSES_DIR}/pdcurses/termattr.c
    ${CURSES_DIR}/pdcurses/touch.c
    ${CURSES_DIR}/pdcurses/util.c
    ${CURSES_DIR}/pdcurses/window.c
)

if(MSVC)
    list(APPEND PDCURSES_SRCS
        ${CURSES_DIR}/wincon/pdcclip.c
        ${CURSES_DIR}/wincon/pdcdisp.c
        ${CURSES_DIR}/wincon/pdcgetsc.c
        ${CURSES_DIR}/wincon/pdckbd.c
        ${CURSES_DIR}/wincon/pdcscrn.c
        ${CURSES_DIR}/wincon/pdcsetsc.c
        ${CURSES_DIR}/wincon/pdcutil.c
    )
endif()

add_library(PDCurses ${PDCURSES_SRCS})

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
include_directories(${CURSES_DIR})

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
    ${SRC_DIR}/texture_map.cpp
    ${SRC_DIR}/startup/menus/main_menu.cpp
    ${SRC_DIR}/curses_state.cpp
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
    ${HDR_DIR}/texture_map.hpp
    ${HDR_DIR}/texture_ref.hpp
    ${HDR_DIR}/startup/menus/main_menu.hpp
    ${HDR_DIR}/curses_state.hpp
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
target_link_libraries(${PROG_NAME} PDCurses)

file(COPY
    ${CMAKE_CURRENT_SOURCE_DIR}/spritesheet.png
    ${CMAKE_CURRENT_SOURCE_DIR}/face.png
    ${CMAKE_CURRENT_SOURCE_DIR}/face2.png
    ${CMAKE_CURRENT_SOURCE_DIR}/face3.png
    ${CMAKE_CURRENT_SOURCE_DIR}/face4.png
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

source_group(startup/menus FILES
    ${SRC_DIR}/startup/menus/main_menu.cpp
    ${HDR_DIR}/startup/menus/main_menu.hpp
)