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
add_executable(day05 day05/main.cpp
        day05/Map.cpp
        day05/Map.h)
add_executable(day06 day06/main.cpp)
add_executable(day07 day07/main.cpp
        day07/Hand.h
        day07/Hand.cpp
        day07/HandPartTwo.cpp
        day07/HandPartOne.cpp
        day07/HandPartOne.h)
add_executable(day08 day08/main.cpp
        day08/Network.cpp
        day08/Network.h)
add_executable(day09 day09/main.cpp)
add_executable(day10 day10/main.cpp
        day10/Pipe.cpp
        day10/Pipe.h)
add_executable(day11 day11/main.cpp
        day11/Galaxy.cpp
        day11/Galaxy.h
        day11/Universe.cpp
        day11/Universe.h)
add_executable(day12 day12/main.cpp)
add_executable(day13 day13/main.cpp)
add_executable(day14 day14/main.cpp)
