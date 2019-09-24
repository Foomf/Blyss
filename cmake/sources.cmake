set(BLYSS_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(BLYSS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

function(ADD_SRC_ROOT FILE_NAME)
    list(APPEND BLYSS_SRCS "${BLYSS_SOURCE_DIR}/${FILE_NAME}.cpp")
    set(BLYSS_SRCS ${BLYSS_SRCS} PARENT_SCOPE)

    source_group(${FOLDER} FILES
        ${BLYSS_SOURCE_DIR}/${FILE_NAME}.cpp
    )
endfunction(ADD_SRC_ROOT)

function(ADD_SRC FILE_NAME FOLDER)
    list(APPEND BLYSS_SRCS "${BLYSS_SOURCE_DIR}/${FOLDER}/${FILE_NAME}.cpp")
    set(BLYSS_SRCS ${BLYSS_SRCS} PARENT_SCOPE)

    source_group(${FOLDER} FILES
        ${BLYSS_SOURCE_DIR}/${FOLDER}/${FILE_NAME}.cpp
    )
endfunction(ADD_SRC)

function(ADD_HDR_ROOT FILE_NAME)
    list(APPEND BLYSS_HDRS "${BLYSS_INCLUDE_DIR}/${FILE_NAME}.hpp")
    set(BLYSS_HDRS ${BLYSS_HDRS} PARENT_SCOPE)

    source_group(${FOLDER} FILES
        ${BLYSS_INCLUDE_DIR}/${FILE_NAME}.hpp
    )
endfunction(ADD_HDR_ROOT)

function(ADD_HDR FILE_NAME FOLDER)
    list(APPEND BLYSS_HDRS "${BLYSS_INCLUDE_DIR}/${FOLDER}/${FILE_NAME}.hpp")
    set(BLYSS_HDRS ${BLYSS_HDRS} PARENT_SCOPE)

    source_group(${FOLDER} FILES
        ${BLYSS_INCLUDE_DIR}/${FOLDER}/${FILE_NAME}.hpp
    )
endfunction(ADD_HDR)

function(ADD_CLASS_ROOT FILE_NAME)
    ADD_SRC_ROOT(${FILE_NAME})
    ADD_HDR_ROOT(${FILE_NAME})
    set(BLYSS_SRCS ${BLYSS_SRCS} PARENT_SCOPE)
    set(BLYSS_HDRS ${BLYSS_HDRS} PARENT_SCOPE)
endfunction(ADD_CLASS_ROOT)

function(ADD_CLASS FILE_NAME FOLDER)
    ADD_SRC(${FILE_NAME} ${FOLDER})
    ADD_HDR(${FILE_NAME} ${FOLDER})
    set(BLYSS_SRCS ${BLYSS_SRCS} PARENT_SCOPE)
    set(BLYSS_HDRS ${BLYSS_HDRS} PARENT_SCOPE)
endfunction(ADD_CLASS)

set(BLYSS_SRCS 
    ${IMGUI_DIR}/examples/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/examples/imgui_impl_opengl3.cpp
)

set(BLYSS_HDRS 
    ${IMGUI_DIR}/examples/imgui_impl_glfw.h
    ${IMGUI_DIR}/examples/imgui_impl_opengl3.h
)

ADD_SRC_ROOT(main)

ADD_CLASS_ROOT(glfw_state)
ADD_CLASS_ROOT(gl_exception)
ADD_CLASS_ROOT(gl_error)
ADD_CLASS_ROOT(shader_build_exception)
ADD_CLASS_ROOT(shader)
ADD_CLASS_ROOT(vertex_buffer_object)
ADD_CLASS_ROOT(vertex_array_object)
ADD_CLASS_ROOT(element_array_buffer)
ADD_CLASS_ROOT(sprite)
ADD_CLASS_ROOT(tile_grid)
ADD_CLASS_ROOT(texture)
ADD_CLASS_ROOT(texture_cache)
ADD_CLASS_ROOT(texture_map)
ADD_CLASS(main_menu startup/menus)
ADD_CLASS(curses_state utils/curses)
ADD_CLASS(window utils/curses)

ADD_HDR_ROOT(texture_ref)
