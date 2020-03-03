

project(stb C CXX)

set(SOURCE_FILES
    include/stb/stb_image.h)

add_library(stb ${SOURCE_FILES})

set_target_properties(stb PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(stb SYSTEM PUBLIC include/)
