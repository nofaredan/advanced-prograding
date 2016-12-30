set(core_SRCS  Cab.cpp Cab.h Driver.cpp Driver.h DriverLocationListener.cpp DriverLocationListener.h FlowManager.cpp FlowManager.h GridManager.cpp GridManager.h GridNode.cpp GridNode.h LuxuryCab.cpp LuxuryCab.h Manager.cpp Manager.h Map.cpp Map.h Node.cpp Node.h Passenger.cpp Passenger.h Point.cpp Point.h Statistics.cpp Statistics.h TaxiCenter.cpp TaxiCenter.h Trip.cpp Trip.h ObstacleNode.cpp ObstacleNode.h)

add_library(core ${core_SRCS})
#add_executable(exe main.cpp).

#target_link_libraries(exe core)

