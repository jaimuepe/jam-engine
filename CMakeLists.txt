
cmake_minimum_required(VERSION 3.9)

set(TARGET_NAME jam-engine)

project(${TARGET_NAME} C CXX)

set(Boost_USE_STATIC_LIBS ON)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(X11 REQUIRED)
find_package(Threads REQUIRED)
find_package(Boost COMPONENTS filesystem REQUIRED)

add_compile_definitions(MYs_DEBUG)

include_directories(
    src
    thirdParty/glad/include
    thirdParty/glfw3/include
    thirdParty/glm
    ${Boost_INCLUDE_DIR})

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

add_subdirectory(thirdParty/glad)
add_subdirectory(thirdParty/glfw3)
add_subdirectory(thirdParty/glm)
add_subdirectory(thirdParty/spdlog)
add_subdirectory(thirdParty/stb)

add_executable(
    ${TARGET_NAME}
    ${SOURCE_FILES})

if(MSVC)
    target_compile_options(${TARGET_NAME} PRIVATE /W4)
else()
    target_compile_options(${TARGET_NAME} PRIVATE -Winline  -Werror
           -pedantic-errors -Wall -Wextra -Wconversion -Wsign-conversion)
endif()

message(STATUS "CMAKE_SOURCE_DIR=${CMAKE_SOURCE_DIR}")

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
	glad 
	stb
    glfw
    spdlog::spdlog
    ${CMAKE_DL_LIBS}
    ${CMAKE_THREAD_LIBS_INIT}
    ${X11_LIBRARIES}
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_TYPEINDEX_LIBRARY})
