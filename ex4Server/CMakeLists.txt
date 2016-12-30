cmake_minimum_required(VERSION 3.6)
project(ex2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp src/Cab.cpp src/Cab.h src/FlowManager.cpp src/FlowManager.h src/Driver.cpp src/Driver.h src/Trip.cpp src/Trip.h src/Passenger.cpp src/Passenger.h src/LuxuryCab.cpp src/LuxuryCab.h src/TaxiCenter.cpp src/TaxiCenter.h src/Statistics.cpp src/Statistics.h src/DriverLocationListener.cpp src/DriverLocationListener.h src/Map.cpp src/Map.h src/Node.cpp src/GridManager.cpp src/GridManager.h src/GridNode.cpp src/Node.h src/GridNode.h src/Manager.cpp src/Manager.h src/Point.h src/Point.cpp src/ObstacleNode.cpp src/ObstacleNode.h src/CommunicationManager.cpp src/CommunicationManager.h)
add_executable(ex2 ${SOURCE_FILES})

target_link_libraries(ex2)
