
cmake_minimum_required(VERSION 3.9)

include(FetchContent)

# ------------------------------------------------------------------------------
# A multi-platform library for OpenGL, OpenGL ES, Vulkan, window and
# input http://www.glfw.org/
FetchContent_Declare(
  extern_glfw

  GIT_REPOSITORY https://github.com/glfw/glfw.git)

FetchContent_GetProperties(extern_glfw)
if(NOT extern_glfw_POPULATED)
  FetchContent_Populate(extern_glfw)
  add_subdirectory(
    ${extern_glfw_SOURCE_DIR}
    ${extern_glfw_BINARY_DIR}
    EXCLUDE_FROM_ALL)
endif()

# ------------------------------------------------------------------------------
# OpenGL Mathematics (GLM) is a header only C++ mathematics library for graphics
# software based on the OpenGL Shading Language (GLSL) specifications.

FetchContent_Declare(
  extern_glm

  GIT_REPOSITORY https://github.com/g-truc/glm.git)

FetchContent_GetProperties(extern_glm)
if(NOT extern_glm_POPULATED)
  FetchContent_Populate(extern_glm)
  add_subdirectory(
    ${extern_glm_SOURCE_DIR}
    ${extern_glm_BINARY_DIR}
    EXCLUDE_FROM_ALL)
endif()

# ------------------------------------------------------------------------------
# Very fast, header-only/compiled, C++ logging library.

FetchContent_Declare(
  extern_spdlog

  GIT_REPOSITORY https://github.com/gabime/spdlog.git)

FetchContent_GetProperties(extern_spdlog)
if(NOT extern_spdlog_POPULATED)
  FetchContent_Populate(extern_spdlog)
  add_subdirectory(
    ${extern_spdlog_SOURCE_DIR}
    ${extern_spdlog_BINARY_DIR}
    EXCLUDE_FROM_ALL)
endif()
