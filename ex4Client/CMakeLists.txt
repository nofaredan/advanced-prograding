cmake_minimum_required(VERSION 3.6)
project(ex4Client)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Driver.cpp Driver.h Cab.cpp Cab.h Trip.cpp Trip.h Point.cpp Point.h Passenger.cpp Passenger.h)
add_executable(ex4Client ${SOURCE_FILES})