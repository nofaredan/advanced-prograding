cmake_minimum_required(VERSION 3.6)
project(ex4Client)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(BOOST_ROOT CACHE PATH "/usr/include/boost/")
set(SOURCE_FILES main.cpp Driver.cpp Driver.h Cab.cpp Cab.h Trip.cpp Trip.h Point.cpp Point.h Passenger.cpp Passenger.h Socket.cpp Socket.h Udp.cpp Udp.h)

find_package(Boost 1.58.0 COMPONENTS serialization system)
include_directories(${Boost_INCLUDE_DIR})

add_executable(ex4Client main.cpp ${SOURCE_FILES})
target_link_libraries(ex4Client ${Boost_LIBRARIES})