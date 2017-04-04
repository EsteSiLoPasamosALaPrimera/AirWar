cmake_minimum_required(VERSION 3.5)
project(AirWar)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Cola_Paginada.h Nodo.h Elemento.h Torre.h TorreMisil.h Lista_Paginada.h Jugador.h Bala.h BalaTorre.h BalaMisil.h Jet.h JetKamikaze.h Bombardero.h EnemyFactory.h Misil.h Laser.h PowerUp.h Pila_Paginada.h)
add_executable(AirWar ${SOURCE_FILES})

INCLUDE_DIRECTORIES( allegro/5.0.11/include )

LINK_DIRECTORIES( allegro/5.0.11/lib )


TARGET_LINK_LIBRARIES(AirWar  allegro_acodec
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