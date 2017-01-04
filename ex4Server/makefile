# hassidr 312486848
# edannof 203345350

Server.out.out: main.o Cab.o Driver.o DriverLocationListener.o FlowManager.o GridManager.o GridNode.o LuxuryCab.o Manager.o Map.o Node.o ObstacleNode.o Passenger.o Point.o Statistics.o TaxiCenter.o Trip.o Socket.o Udp.o
	g++ -std=c++0x main.o Cab.o Driver.o DriverLocationListener.o FlowManager.o GridManager.o GridNode.o LuxuryCab.o Manager.o Map.o Node.o ObstacleNode.o Passenger.o Point.o Statistics.o TaxiCenter.o Trip.o Socket.o Udp.o -lboost_serialization -I. -o Server.out

main.o: src/main.cpp src/FlowManager.h
	g++ -std=c++0x -c src/main.cpp

Cab.o: src/Cab.cpp src/Cab.h src/Trip.h src/Point.h src/Passenger.h
	g++ -std=c++0x -c src/Cab.cpp

Driver.o: src/Driver.cpp src/Driver.h src/Cab.h src/Trip.h src/Map.h src/Statistics.h
	g++ -std=c++0x -c src/Driver.cpp

DriverLocationListener.o: src/DriverLocationListener.cpp src/DriverLocationListener.h
	g++ -std=c++0x -c src/DriverLocationListener.cpp

FlowManager.o: src/FlowManager.cpp src/FlowManager.h
	g++ -std=c++0x -c src/FlowManager.cpp

GridManager.o: src/GridManager.cpp src/GridManager.h
	g++ -std=c++0x -c src/GridManager.cpp

GridNode.o: src/GridNode.cpp src/GridNode.h
	g++ -std=c++0x -c src/GridNode.cpp

LuxuryCab.o: src/LuxuryCab.cpp src/LuxuryCab.h
	g++ -std=c++0x -c src/LuxuryCab.cpp

Manager.o: src/Manager.cpp src/Manager.h
	g++ -std=c++0x -c src/Manager.cpp

Map.o: src/Map.cpp src/Map.h
	g++ -std=c++0x -c src/Map.cpp

Node.o: src/Node.cpp src/Node.h
	g++ -std=c++0x -c src/Node.cpp

ObstacleNode.o: src/ObstacleNode.cpp src/ObstacleNode.h
	g++ -std=c++0x -c src/ObstacleNode.cpp

Passenger.o: src/Passenger.cpp src/Passenger.h
	g++ -std=c++0x -c src/Passenger.cpp

Point.o: src/Point.cpp src/Point.h
	g++ -std=c++0x -c src/Point.cpp

Statistics.o: src/Statistics.cpp src/Statistics.h
	g++ -std=c++0x -c src/Statistics.cpp

TaxiCenter.o: src/TaxiCenter.cpp src/TaxiCenter.h
	g++ -std=c++0x -c src/TaxiCenter.cpp

Trip.o: src/Trip.cpp src/Trip.h
	g++ -std=c++0x -c src/Trip.cpp

Socket.o: src/Socket.cpp src/Socket.h
	g++ -std=c++0x -c src/Socket.cpp

Udp.o: src/Udp.cpp src/Udp.h
	g++ -std=c++0x -c src/Udp.cpp

clean:
	rm -f *.o a.out

