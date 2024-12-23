cmake_minimum_required(VERSION 3.16.3)

project(TETRIS)

set(SOURCES
    types/core.cpp 
    types/environment.cpp 
    types/pixel.cpp 
    types/sdl.cpp 
    types/tetramino.cpp 
    types/tetrisroom.cpp
    main.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    SDL2)
target_compile_options(${PROJECT_NAME}
    PRIVATE
    -Werror 
    -Wall 
    -std=c++20
    -Wconversion
    -Werror=narrowing
    -O2
    -g0
    -march=native
    -flto)
    
