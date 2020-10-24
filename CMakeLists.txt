cmake_minimum_required(VERSION 3.11.3)
project(catch_game)

# TODO: Graphics dependencies
#find_package(XXXXXXXXX VV.VV REQUIRED)
#include_directories(${XXXXXXXXX_INCLUDE_DIRS})
#link_directories(${XXXXXXXXX_LIBRARY_DIRS})
#add_definitions(${XXXXXXXXX_DEFINITIONS})

# Set up additional compile flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra -Werror -pthread")

# Headers and source files
include_directories(include)
file(GLOB catch_game_SOURCES src/*.cpp)

# Generate executable
add_executable(catch_game ${catch_game_SOURCES})
