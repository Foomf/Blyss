# --------------------------------------------------------- #
#  Dear IMGUI                                               #
# --------------------------------------------------------- #
set(IMGUI_DIR lib/imgui)
set(IMGUI_LIB imgui)
set(IMGUI_INCLUDE_DIR ${IMGUI_DIR})

add_compile_definitions(IMGUI_IMPL_OPENGL_LOADER_GLAD)

add_library(${IMGUI_LIB}
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

target_include_directories(${IMGUI_LIB} PUBLIC ${IMGUI_INCLUDE_DIR})