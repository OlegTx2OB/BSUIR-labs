cmake_minimum_required(VERSION 3.26)
project(full_3_laba)

set(CMAKE_CXX_STANDARD 17)

add_executable(full_3_laba main.cpp
        CurrentTime.cpp
        CurrentTime.h
        Event.cpp
        Event.h
        Menu.cpp
        Menu.h
        SecondaryFunctions.cpp
        SecondaryFunctions.h)
