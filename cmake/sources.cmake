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
