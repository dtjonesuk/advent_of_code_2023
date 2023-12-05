cmake_minimum_required(VERSION 3.26)
project(advent_of_code_2023)

set(CMAKE_CXX_STANDARD 23)

add_executable(day01 day01/main.cpp)
add_executable(day02 day02/main.cpp
        day02/Game.cpp)
add_executable(day03 day03/main.cpp
        day03/Schematic.cpp
        day03/Schematic.h)
add_executable(day04 day04/main.cpp
        day04/ScratchCard.cpp
        day04/ScratchCard.h
        day04/CardCounter.cpp
        day04/CardCounter.h)
add_executable(day05 day05/main.cpp)
