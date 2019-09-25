cmake_minimum_required(VERSION 3.12)

# --------------------------------------------------------- #
# Project declaration                                       #
# --------------------------------------------------------- #
set(PROG_NAME Blyss)
project (${PROG_NAME})

# --------------------------------------------------------- #
# C++ 17 standard                                           #
# --------------------------------------------------------- #
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --------------------------------------------------------- #
# Include modules                                           #
# --------------------------------------------------------- #
include(cmake/embed.cmake)
include(cmake/add.cmake)

# --------------------------------------------------------- #
# Include dependencies                                      #
# --------------------------------------------------------- #
include(cmake/lib/gladimpl.cmake)
include(cmake/lib/glfw.cmake)
include(cmake/lib/glm.cmake)
include(cmake/lib/imgui.cmake)
include(cmake/lib/pdcurses.cmake)
include(cmake/lib/spdlog.cmake)
include(cmake/lib/stb.cmake)
include(cmake/lib/libuv.cmake)

# --------------------------------------------------------- #
# Include sources                                           #
# --------------------------------------------------------- #
include(cmake/sources.cmake)

# --------------------------------------------------------- #
# Blyss version                                             #
# --------------------------------------------------------- #
add_compile_definitions(BLYSS_VERSION_MAJOR="0")
add_compile_definitions(BLYSS_VERSION_MINOR="0")
add_compile_definitions(BLYSS_VERSION_PATCH="1")

# --------------------------------------------------------- #
# Blyss Compile definitions                                 #
# --------------------------------------------------------- #
set(SHADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/shaders CACHE PATH "Shaders folder")
add_compile_definitions(SHADER_DIR="${SHADER_DIR}")

# --------------------------------------------------------- #
# Blyss executable                                          #
# --------------------------------------------------------- #
add_executable(${PROG_NAME} ${BLYSS_SRCS} ${BLYSS_HDRS})

# --------------------------------------------------------- #
# Include directories                                       #
# --------------------------------------------------------- #
target_include_directories(${PROG_NAME} PUBLIC
    ${BLYSS_INCLUDE_DIR}
    ${STB_INCLUDE_DIR}
)

# --------------------------------------------------------- #
# Library linking                                           #
# --------------------------------------------------------- #
target_link_libraries(${PROG_NAME}
    gladimpl
    glfw
    ${SPDLOG_LIB}
    ${IMGUI_LIB}
    ${PDCURSES_LIB}
    ${LIBUV_LIB}
    ${GLM_LIB}
)