# hassidr 312486848
# edannof 203345350

Client.out: main.o Cab.o Driver.o Passenger.o Point.o Trip.o Udp.o Socket.o
	g++ -std=c++0x main.o Cab.o Driver.o Point.o Trip.o Udp.o Socket.o -lboost_serialization -I. -o Client.out

main.o: main.cpp Driver.h Udp.h
	g++ -std=c++0x -c main.cpp

Cab.o: Cab.cpp Cab.h Trip.h Point.h Passenger.h
	g++ -std=c++0x -c  Cab.cpp

Driver.o:  Driver.cpp  Driver.h  Cab.h  Trip.h
	g++ -std=c++0x -c  Driver.cpp

Passenger.o:  Passenger.cpp  Passenger.h
	g++ -std=c++0x -c  Passenger.cpp

Trip.o:  Trip.cpp  Trip.h
	g++ -std=c++0x -c  Trip.cpp

Socket.o:  Socket.cpp  Socket.h
	g++ -std=c++0x -c  Socket.cpp

Udp.o:  Udp.cpp  Udp.h
	g++ -std=c++0x -c  Udp.cpp

Point.o: Point.cpp Point.h
	g++ -std=c++0x -c Point.cpp

clean:
	rm -f *.o a.out

