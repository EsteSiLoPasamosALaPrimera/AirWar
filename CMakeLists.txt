cmake_minimum_required(VERSION 3.6)
project(AirWar__)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
add_executable(AirWar__ ${SOURCE_FILES})

INCLUDE_DIRECTORIES( allegro/5.0.11/include )

LINK_DIRECTORIES( allegro/5.0.11/lib )

TARGET_LINK_LIBRARIES(AirWar__  allegro_acodec
        allegro_audio
        allegro_color
        allegro_dialog
        allegro_image
        allegro_main
        allegro_memfile
        allegro_physfs
        allegro_primitives
        allegro_ttf
        allegro_font
        allegro)