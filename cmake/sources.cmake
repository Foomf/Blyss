set(BLYSS_SRCS 
    ${IMGUI_DIR}/examples/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/examples/imgui_impl_opengl3.cpp
)

set(BLYSS_HDRS 
    ${IMGUI_DIR}/examples/imgui_impl_glfw.h
    ${IMGUI_DIR}/examples/imgui_impl_opengl3.h
)

# --------------------------------------------------------- #
# main.cpp                                                  #
# --------------------------------------------------------- #
ADD_SRC_ROOT(main)

# --------------------------------------------------------- #
# Text files                                                #
# --------------------------------------------------------- #
EMBED_FILE("banner.txt" "include/banner.hpp" "banner_text")

# --------------------------------------------------------- #
# Root dir classes                                          #
# --------------------------------------------------------- #
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

# --------------------------------------------------------- #
# Root dir headers                                          #
# --------------------------------------------------------- #
ADD_HDR_ROOT(texture_ref)

# --------------------------------------------------------- #
# server                                                    #
# --------------------------------------------------------- #
ADD_CLASS(server server)
ADD_CLASS(perf_watcher server)
ADD_CLASS(world server)
ADD_CLASS(map server)
ADD_CLASS(cell server)

# --------------------------------------------------------- #
# client                                                    #
# --------------------------------------------------------- #

# --------------------------------------------------------- #
# startup/menus                                             #
# --------------------------------------------------------- #
ADD_CLASS(main_menu startup/menus)

# --------------------------------------------------------- #
# utils/curses                                              #
# --------------------------------------------------------- #
ADD_CLASS(curses_state utils/curses)
ADD_CLASS(window utils/curses)
