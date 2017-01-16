cmake_minimum_required(VERSION 3.6)

project(ex4Server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(BOOST_ROOT CACHE PATH "/usr/include/boost/")

set(SOURCE_FILES  Cab.cpp Cab.h Driver.cpp Driver.h DriverLocationListener.cpp DriverLocationListener.h
        FlowManager.cpp FlowManager.h GridManager.cpp GridManager.h GridNode.cpp GridNode.h LuxuryCab.cpp
        LuxuryCab.h Manager.cpp Manager.h Map.cpp Map.h Node.cpp Node.h Passenger.cpp Passenger.h Point.cpp
        Point.h Statistics.cpp Statistics.h TaxiCenter.cpp TaxiCenter.h Trip.cpp Trip.h ObstacleNode.cpp ObstacleNode.h)

add_library(core ${core_SRCS})

find_package(Boost 1.58.0 COMPONENTS serialization system)
include_directories(${Boost_INCLUDE_DIR})

add_executable(ex4Server main.cpp ${SOURCE_FILES})
target_link_libraries(ex4Server ${Boost_LIBRARIES})
#add_executable(exe main.cpp).

#target_link_libraries(exe core)

