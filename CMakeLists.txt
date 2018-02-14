cmake_minimum_required(VERSION 3.5.2)
project(GameOfLife)
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Headers
include_directories(include)

# Source
file(GLOB SOURCES "source/*.cpp")

# SFML libraries
# include files are already dealt with

# Compiler flags
add_definitions(-ggdb -Wpedantic -Wall -Wextra)

add_executable(GameOfLife ${SOURCES})

# SFML libs
target_link_libraries(GameOfLife -lsfml-graphics -lsfml-window -lsfml-system)
