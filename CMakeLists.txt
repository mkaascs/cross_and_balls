cmake_minimum_required(VERSION 3.10)
project(cross_ball C)

set(CMAKE_C_STANDARD 11)

set(SDL2_PATH "/opt/homebrew/opt/sdl2")
set(SDL2_GFX_PATH "/opt/homebrew/Cellar/sdl2_gfx/1.0.4")
set(SDL2_TTF_PATH "/opt/homebrew/Cellar/sdl2_ttf/2.24.0")

include_directories(
        ${SDL2_PATH}/include/SDL2
        ${SDL2_GFX_PATH}/include/SDL2
        ${SDL2_TTF_PATH}/include/SDL2
)

link_directories(
        ${SDL2_PATH}/lib
        ${SDL2_GFX_PATH}/lib
        ${SDL2_TTF_PATH}/lib
)

add_executable(cross_ball
        main.c
        game/domain/entities/game.c
        game/domain/entities/game.h
        game/views/layout/layout.h
        game/views/layout/layout.c
        game/controllers/controllers.h
        game/views/board/views.h
        game/views/board/views.c
        game/domain/query/moves.h
        game/domain/query/moves.c
        game/controllers/board/board.c
        memstat/memstat.c
        memstat/memstat.h
        game/views/assets.h
        game/views/assets.c
        game/controllers/states.h
        game/controllers/board/states.c
        game/controllers/menu/menu.c
        game/controllers/menu/states.c
        game/domain/entities/leaderboard.h
        game/domain/entities/leaderboard.c
        game/views/menu/views.h
        game/views/menu/views.c
        game/controllers/leaderboard/leaderboard.c
        game/controllers/leaderboard/states.c
        game/views/leaderboard/views.h
        game/views/leaderboard/views.c
        game/views/primitives/primitives.h
        game/views/primitives/primitives.c
)

# Линкуем библиотеки
target_link_libraries(cross_ball
        SDL2
        SDL2_gfx
        SDL2_ttf
)