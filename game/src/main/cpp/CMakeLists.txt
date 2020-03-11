cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_VERBOSE_MAKEFILE on)

if (NOT DEFINED LIB_GAME)
    message(FATAL_ERROR "You must set argument \"LIB_GAME\" with library name...")
endif ()

file(GLOB_RECURSE
    GAME_CPP
        game/Main/*.cpp
        game/Graphic/*.cpp
        game/Particles/*.cpp
        game/Shaders/*.cpp
        game/Sound/*.cpp
        game/Textures/*.cpp
)

add_library(${LIB_GAME}
    SHARED
        # Main JNI source
        game/gamelib.cpp
        # Game source
        ${GAME_CPP}
)

set_target_properties(${LIB_GAME}
    PROPERTIES LIBRARY_OUTPUT_DIRECTORY
        "${CMAKE_CURRENT_SOURCE_DIR}/../../../../lib/${ANDROID_ABI}"
)

target_link_libraries(${LIB_GAME}
    PRIVATE
        android
        log
        GLESv2
        OpenSLES
)

target_include_directories(${LIB_GAME}
    PUBLIC
        game
)