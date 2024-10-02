cmake_minimum_required(VERSION 3.28)
project(lab1)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab1 main.cpp
        PowerManager.cpp
        PowerManager.h
        BatteryInfo.cpp
        BatteryInfo.h)

find_library(POWRPROF_LIB PowrProf.lib)
target_link_libraries(lab1 PRIVATE PowrProf SetupAPI)