cmake_minimum_required(VERSION 3.19)
project(ConnectiveGames)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/circle.vs ${CMAKE_CURRENT_SOURCE_DIR}/circle.fs
        ${CMAKE_CURRENT_SOURCE_DIR}/trapezium.vs ${CMAKE_CURRENT_SOURCE_DIR}/trapezium.fs
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(ConnectiveGames main.cpp glad.c Frame.cpp Matrix3x3.cpp Human.cpp Renderer.cpp Sprite.cpp Animation.cpp)

target_include_directories(ConnectiveGames PRIVATE include ${SDL_BINARY_DIR}/include)
target_link_libraries(ConnectiveGames -lSDL2 -ldl -pthread)

