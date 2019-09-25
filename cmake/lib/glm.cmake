# --------------------------------------------------------- #
# GLM                                                       #
# --------------------------------------------------------- #
set(GLM_DIR lib/glm)
set(GLM_LIB glm)

set(GLM_TEST_ENABLE OFF CACHE BOOL "" FORCE)

add_subdirectory(${GLM_DIR})