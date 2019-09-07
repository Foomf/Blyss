set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

cmake_minimum_required(VERSION 2.8.12)
set(PROG_NAME Thimble)
project (${PROG_NAME})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(lib/glfw)

set(HDR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

include_directories(${HDR_DIR})

set(SRCS
    ${SRC_DIR}/main.cpp
)

set (HDRS
)

add_executable(${PROG_NAME} ${SRCS} ${HDRS})
target_link_libraries(${PROG_NAME} glfw)
