cmake_minimum_required(VERSION 3.26)
project(advent_of_code_2023)

set(CMAKE_CXX_STANDARD 23)

add_executable(day01 day01/main.cpp)
add_executable(day02 day02/main.cpp
        day02/Game.cpp)
add_executable(day03 day03/main.cpp
        day03/Schematic.cpp
        day03/Schematic.h)
