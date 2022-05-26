cmake_minimum_required(VERSION 3.19)
project(ConnectiveGames)

find_package(SDL2 REQUIRED)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/circle.vs ${CMAKE_CURRENT_SOURCE_DIR}/circle.fs
        ${CMAKE_CURRENT_SOURCE_DIR}/trapezium.vs ${CMAKE_CURRENT_SOURCE_DIR}/trapezium.fs
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(ConnectiveGames main.cpp glad.c Frame.cpp Matrix3x3.cpp Human.cpp Renderer.cpp Sprite.cpp Animation.cpp)

target_include_directories(ConnectiveGames PRIVATE include ${SDL2_INCLUDE_DIRS})
target_link_libraries(ConnectiveGames ${SDL2_LIBRARIES} -ldl -pthread)