# hassidr 312486848
# edannof 203345350

a.out: main.o Cab.o Driver.o Passenger.o Point.o Trip.o
	g++ -std=c++0x main.o Cab.o Driver.o Point.o Trip.o

main.o: main.cpp
	g++ -std=c++0x -c main.cpp

Cab.o: Cab.cpp Cab.h Trip.h  Point.h Passenger.h
	g++ -std=c++0x -c  Cab.cpp

Driver.o:  Driver.cpp  Driver.h  Cab.h  Trip.h
	g++ -std=c++0x -c  Driver.cpp

Passenger.o:  Passenger.cpp  Passenger.h
	g++ -std=c++0x -c  Passenger.cpp

Point.o:  Point.cpp  Point.h
	g++ -std=c++0x -c  Point.cpp

Trip.o:  Trip.cpp  Trip.h
	g++ -std=c++0x -c  Trip.cpp

clean:
	rm -f *.o a.out

