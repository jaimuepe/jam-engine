
cmake_minimum_required(VERSION 3.9)

project(stb)

set(SOURCE_FILES
    include/stb/stb_image.h)

add_library(stb INTERFACE)
target_include_directories(stb INTERFACE include/)