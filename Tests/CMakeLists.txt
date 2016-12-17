cmake_minimum_required(VERSION 3.3)

project(Test)


include(CTest)

SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -lpthread")
set(test_SRCS TestCab.cpp TestDriver.cpp TestFlowManager.cpp TestGridManager.cpp TestGridNode.cpp TestPassenger.cpp TestStatistics.cpp TestTaxiCenter.cpp TestTrip.cpp)
add_executable(runUnitTests gtest.cpp ${test_SRCS})
target_link_libraries(runUnitTests gtest gmock core)
add_test(runUnitTests runUnitTests) #included in all tutorials but I don't know what it actually does.



