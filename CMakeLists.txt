cmake_minimum_required(VERSION 3.11.3)
project(catch_game)

# SDL2 library
find_package(SDL2 REQUIRED)

# Set up additional compile flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra -Werror -pthread")

# Headers and source files
include_directories(${SDL2_INCLUDE_DIRS} include include/Factories include/Fallers include/Game)
file(GLOB catch_game_SOURCES src/*.cpp src/Factories/*.cpp src/Fallers/*.cpp src/Game/*.cpp)

# Generate executable
add_executable(catch_game ${catch_game_SOURCES})
target_link_libraries(catch_game stdc++fs ${SDL2_LIBRARIES} SDL2_image)
