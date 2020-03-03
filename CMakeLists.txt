cmake_minimum_required(VERSION 3.9)

set(TARGET_NAME jam-engine)

project(${TARGET_NAME} C CXX)

find_package(glm REQUIRED)
find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)
find_package(Boost COMPONENTS filesystem REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
    /usr/local/include
    src
    include)

link_directories(/usr/local/lib)

set(SOURCE_FILES
    src/main.cpp
    src/world.h
    src/world.cpp
    src/game.h
    src/game.cpp
    src/gametime.h
    src/gametime.cpp
    src/window.h
    src/window.cpp
    src/input.h
    src/input.cpp
    src/inputcomponenttest.h
    src/objects/camera.h
    src/objects/transform.h
    src/objects/orthocamera.h
    src/objects/orthocamera.cpp
    src/objects/entity.h
    src/objects/entity.cpp
    src/objects/irenderablecomponent.h
    src/objects/iupdateablecomponent.h
    src/objects/component.h
    src/objects/component.cpp
    src/graphics/spriterenderer.h
    src/graphics/spriterenderer.cpp
    src/graphics/shader.h
    src/graphics/shader.cpp
    src/graphics/graphiccontext.h
    src/constructorContext.h
    src/resourceManager.h
    src/resourceManager.cpp
    src/graphics/texture2d.h
    src/graphics/texture2d.cpp
    src/logger.h
    src/logger.cpp)

set(HEADER_FILES)

add_subdirectory(thirdParty/glad)
add_subdirectory(thirdParty/stb)

add_executable(
    ${TARGET_NAME}
    ${SOURCE_FILES}
    ${HEADER_FILES})

if(MSVC)
  target_compile_options(${TARGET_NAME} PRIVATE /W4 /WX)
else()
  target_compile_options(${TARGET_NAME} PRIVATE -Winline -Werror
      #[[ -pedantic-errors ]]
      -Wall -Wextra -Wconversion -Wsign-conversion)
endif()

if (EXISTS "${CMAKE_SOURCE_DIR}/resources")

    add_custom_target(copy_res_directory ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/resources"
            "${CMAKE_BINARY_DIR}/resources"
        COMMENT "Copy res directory to build tree"
        VERBATIM)

endif()

target_link_libraries(
    ${TARGET_NAME}
    PRIVATE glad stb fmt GL
    glfw3 X11 pthread dl
    spdlog::spdlog
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_TYPEINDEX_LIBRARY})
