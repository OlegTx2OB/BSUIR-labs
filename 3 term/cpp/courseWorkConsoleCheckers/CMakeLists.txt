cmake_minimum_required(VERSION 3.26)
project(courseWorkConsoleCheckers)

set(CMAKE_CXX_STANDARD 17)

add_executable(courseWorkConsoleCheckers main.cpp
        GameProcess.cpp
        GameProcess.h
        Board.cpp
        Board.h
        Figure.cpp
        Figure.h
)
