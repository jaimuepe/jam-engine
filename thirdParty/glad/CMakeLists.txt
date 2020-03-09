cmake_minimum_required(VERSION 3.9)

project(glad)

set(SOURCE_FILES
    include/KHR/khrplatform.h
    include/glad/glad.h
    src/glad.c)

add_library(glad ${SOURCE_FILES})
target_include_directories(glad PUBLIC include/)
