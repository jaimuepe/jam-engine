cmake_minimum_required(VERSION 3.9)

project(stb)

add_library(stb
    dummy.cpp
    include/stb/stb_image.h)

target_include_directories(stb PUBLIC include/)

