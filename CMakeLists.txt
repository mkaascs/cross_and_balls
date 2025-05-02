cmake_minimum_required(VERSION 3.10)
project(cross_ball C)

set(CMAKE_C_STANDARD 11)

set(SDL2_PATH "/opt/homebrew/opt/sdl2")
set(SDL2_INCLUDE_DIR "${SDL2_PATH}/include/SDL2")
set(SDL2_LIBRARY "${SDL2_PATH}/lib/libSDL2.dylib")

include_directories(${SDL2_INCLUDE_DIR})

add_executable(cross_ball main.c
        game/game.c
        game/game.h
        game/views/board_view.h
        game/config/config.h
        game/config/config.c
        game/views/symbols_view.h
        game/views/board_view.c)

target_link_libraries(cross_ball ${SDL2_LIBRARY})