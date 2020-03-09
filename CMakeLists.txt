
cmake_minimum_required(VERSION 3.9)

set(TARGET_NAME jam-engine)

project(${TARGET_NAME} C CXX)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(OPENGL ON CACHE BOOL "" FORCE)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (UNIX)
    find_package(X11 REQUIRED)
endif()

find_package(Threads REQUIRED)
find_package(Boost COMPONENTS filesystem REQUIRED)

set(HEADER_FILES
    src/game.h
    src/gameinitdata.h
    src/gametime.h
    src/io/input.h
    src/io/keys.h
    src/objects/component.h
    src/objects/constructorContext.h
    src/objects/entity.h
    src/objects/world.h
    src/graphics/camera.h
    src/graphics/graphicsdevice.h
    src/objects/transform.h
    src/graphics/rendercontext.h
    src/graphics/orthocamera.h
    src/graphics/shader.h
    src/graphics/spriterenderer.h
    src/graphics/texture2d.h
    src/resourcepool.h
    src/utils/constants.h
    src/utils/logger.h
    src/utils/macros.h
    src/utils/xplatformdefinitions.h)

set(SOURCE_FILES
    src/game.cpp
    src/gametime.cpp
    src/io/input.cpp
    src/objects/component.cpp
    src/objects/entity.cpp
    src/objects/world.cpp
    src/graphics/graphicsdevice.cpp
    src/graphics/orthocamera.cpp
    src/graphics/shader.cpp
    src/graphics/spriterenderer.cpp
    src/graphics/texture2d.cpp
    src/resourcepool.cpp)

set(COMPILE_DEFINITIONS
    STB_IMAGE_IMPLEMENTATION)

set(TARGET_LIBRARIES
    glm
    spdlog
    stb
    ${CMAKE_DL_LIBS}
    ${CMAKE_THREAD_LIBS_INIT}
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_TYPEINDEX_LIBRARY})

if (UNIX)
    list(APPEND TARGET_LIBRARIES
        ${X11_LIBRARIES})
endif()

if (OPENGL)
    list(APPEND SOURCE_FILES
        x/graphics/graphicsdeviceopengl.cpp
        x/graphics/shaderopengl.cpp
        x/io/inputopengl.cpp)

    list(APPEND HEADER_FILES
        x/graphics/graphicsdeviceopengl.h
        x/graphics/shaderopengl.h
        x/io/inputopengl.h)

    list(APPEND COMPILE_DEFINITIONS OPENGL)
    list(APPEND COMPILE_DEFINITIONS GLFW_INCLUDE_NONE)

    list(APPEND TARGET_LIBRARIES
        glfw
        glad)
endif()

add_library(${TARGET_NAME} ${SOURCE_FILES} ${HEADER_FILES})

target_compile_definitions(${TARGET_NAME} PUBLIC ${COMPILE_DEFINITIONS})

target_include_directories(
    ${TARGET_NAME}
    PUBLIC
    src
    x)

if(MSVC)
    target_compile_options(${TARGET_NAME} PRIVATE /W4)
else()
    target_compile_options(${TARGET_NAME} PRIVATE -Winline
           -pedantic-errors -Wall -Wextra -Wconversion -Wsign-conversion)
endif()

add_subdirectory(thirdParty/glad)
add_subdirectory(thirdParty/glfw-3.3.2)
add_subdirectory(thirdParty/glm-0.9.9.7)
add_subdirectory(thirdParty/spdlog-1.5.0)
add_subdirectory(thirdParty/stb)

target_link_libraries(
    ${TARGET_NAME}
    ${TARGET_LIBRARIES})
