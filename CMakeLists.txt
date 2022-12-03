cmake_minimum_required(VERSION 3.23)
project(CP411_SnakesAndLadders)

set(CMAKE_CXX_STANDARD 14)

include_directories(BoardGame)
include_directories(images)

add_executable(CP411_SnakesAndLadders
        BoardGame/main.cpp
        BoardGame/main.h)
