cmake_minimum_required(VERSION 3.26)
project(lab7)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab7 main.cpp
        MenuClass.cpp
        MenuClass.h
        Structure.cpp
        Structure.h
        BinFile.cpp
        BinFile.h
        TxtFile.cpp
        TxtFile.h
)
