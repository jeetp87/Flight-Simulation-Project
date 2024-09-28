cmake_minimum_required(VERSION 3.26)
project(FP02)

set(CMAKE_CXX_STANDARD 17)

add_executable(FP02 main.cpp
        Passenger.h
        Flight.h
        Airport.h
        Passenger.cpp
        Flight.cpp
        Airport.cpp)
