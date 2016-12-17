cmake_minimum_required(VERSION 3.6)
project(ex3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_subdirectory(lib/googletest-master)

include_directories(lib/googletest-master/googletest/include)

set(SOURCE_FILES main.cpp Tests/TestTrip.cpp Tests/TestTaxiCenter.cpp Tests/TestStatistics.cpp Tests/TestPassenger.cpp Tests/TestGridNode.cpp Tests/TestFlowManager.cpp Tests/TestDriver.cpp Tests/gtest.cpp Tests/TestCab.cpp Tests/TestGridManager.cpp src/Cab.cpp src/Cab.h src/Driver.h src/Driver.cpp src/DriverLocationListener.cpp src/DriverLocationListener.h src/FlowManager.cpp src/Driver.cpp src/FlowManager.h src/GridManager.cpp src/GridManager.h src/GridNode.cpp src/GridNode.h src/LuxuryCab.cpp src/LuxuryCab.h src/Manager.cpp src/Manager.h src/Manager.cpp src/Manager.h src/Map.cpp src/Map.h src/ObstacleNode.cpp src/ObstacleNode.h src/Node.cpp src/Node.h src/Passenger.cpp src/Passenger.h src/Point.cpp src/Point.h src/Statistics.cpp src/Statistics.h src/TaxiCenter.cpp src/TaxiCenter.h src/Trip.cpp src/Trip.h)
add_executable(ex3 ${SOURCE_FILES} Tests/TestTrip.cpp Tests/TestTaxiCenter.cpp Tests/TestStatistics.cpp Tests/TestPassenger.cpp Tests/TestGridNode.cpp Tests/TestFlowManager.cpp Tests/TestDriver.cpp Tests/gtest.cpp Tests/TestCab.cpp Tests/TestGridManager.cpp src/Cab.cpp src/Cab.h src/Driver.h src/Driver.cpp src/DriverLocationListener.cpp src/DriverLocationListener.h src/FlowManager.cpp src/Driver.cpp src/FlowManager.h src/GridManager.cpp src/GridManager.h src/GridNode.cpp src/GridNode.h src/LuxuryCab.cpp src/LuxuryCab.h src/Manager.cpp src/Manager.h src/Manager.cpp src/Manager.h src/Map.cpp src/Map.h src/ObstacleNode.cpp src/ObstacleNode.h src/Node.cpp src/Node.h src/Passenger.cpp src/Passenger.h src/Point.cpp src/Point.h src/Statistics.cpp src/Statistics.h src/TaxiCenter.cpp src/TaxiCenter.h src/Trip.cpp src/Trip.h)
target_link_libraries(ex3 gtest gtest_main)