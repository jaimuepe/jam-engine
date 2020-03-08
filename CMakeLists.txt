
cmake_minimum_required(VERSION 3.9)

set(TARGET_NAME jam-engine)

project(${TARGET_NAME} C CXX)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(X11 REQUIRED)
find_package(Threads REQUIRED)
find_package(Boost COMPONENTS filesystem REQUIRED)

# add_compile_definitions(MYs_DEBUG)

set(SOURCE_FILES
    src/main.cpp
    src/game.h
    src/game.cpp
    src/gametime.h
    src/gametime.cpp
    src/window.h
    src/window.cpp
    src/shipcontroller.h
    src/shipcontroller.cpp
    src/io/input.h
    src/io/input.cpp
    src/io/keys.h
    src/objects/component.h
    src/objects/component.cpp
    src/objects/constructorContext.h
    src/objects/entity.h
    src/objects/entity.cpp
    src/objects/transform.h
    src/objects/world.h
    src/objects/world.cpp
    src/graphics/camera.h
    src/graphics/rendercontext.h
    src/graphics/orthocamera.h
    src/graphics/orthocamera.cpp
    src/graphics/shader.h
    src/graphics/shader.cpp
    src/graphics/spriterenderer.h
    src/graphics/spriterenderer.cpp
    src/graphics/texture2d.h
    src/graphics/texture2d.cpp
    src/resourcepool.h
    src/resourcepool.cpp
    src/utils/constants.h
    src/utils/logger.h
    src/utils/macros.h)

add_executable(${TARGET_NAME} "")

target_sources(
    ${TARGET_NAME}
    PRIVATE
    ${SOURCE_FILES})

target_include_directories(
    ${TARGET_NAME}
    PRIVATE
    src)

add_subdirectory(extern)
add_subdirectory(thirdParty/glad)
add_subdirectory(thirdParty/stb)

if(MSVC)
    target_compile_options(${TARGET_NAME} PRIVATE /W4)
else()
    target_compile_options(${TARGET_NAME} PRIVATE -Winline
           -pedantic-errors -Wall -Wextra -Wconversion -Wsign-conversion)
endif()

if (EXISTS "${CMAKE_SOURCE_DIR}/resources")
    add_custom_target(copy-resources ALL
        COMMAND ${CMAKE_COMMAND} -E remove_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/resources"
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                "${CMAKE_SOURCE_DIR}/resources"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/resources"
        COMMENT "Copy res directory to build tree"
        VERBATIM)
endif()

target_link_libraries(
    ${TARGET_NAME}
    PRIVATE 
    stb
    glad
    glm
    glfw
    spdlog
    ${CMAKE_DL_LIBS}
    ${CMAKE_THREAD_LIBS_INIT}
    ${X11_LIBRARIES}
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_TYPEINDEX_LIBRARY})
