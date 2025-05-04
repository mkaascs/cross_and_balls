cmake_minimum_required(VERSION 3.10)
project(cross_ball C)

set(CMAKE_C_STANDARD 11)

set(SDL2_PATH "/opt/homebrew/opt/sdl2")
set(SDL2_GFX_PATH "/opt/homebrew/Cellar/sdl2_gfx/1.0.4")

include_directories(
        ${SDL2_PATH}/include/SDL2
        ${SDL2_GFX_PATH}/include/SDL2
)

link_directories(
        ${SDL2_PATH}/lib
        ${SDL2_GFX_PATH}/lib
)

add_executable(cross_ball
        main.c
        game/domain/game.c
        game/domain/game.h
        game/views/window/size.h
        game/views/window/size.c
        game/controllers/controllers.h
        game/views/views.h
        game/views/views.c
        game/controllers/controllers.c
        game/views/primitives/button.h
        game/domain/query/moves.h
        game/domain/query/moves.c
)

target_link_libraries(cross_ball
        SDL2
        SDL2_gfx
)