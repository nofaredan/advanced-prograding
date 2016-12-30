//
// Created by nofar edan on 29/11/2016.
//

#ifndef EX2_TRIP_H
#define EX2_TRIP_H

#include "Point.h"
#include "Passenger.h"
#include <vector>
using namespace std;
class Trip {
private:
    int rideId;
    int meterPassed;
    Point currentPlace;
    Point end;
    int numPassengers;
    double tariff;
    vector<Passenger*> arrPassengers;

public:
    Trip(){};
    Trip(int id, Point startPoint, Point endPoint, int passengers,double tariffRide);
    void move();
    void addPassenger();
    int getMeterPassed();
    int getNumPassengers();
    vector<Passenger*> getArrPassengers();
    int getRideId();
    Point getCurrentPlace();
    Point getEnd();
    double getTariff();
    void setCurrentPlace(Point place);
};

#endif //EX2_TRIP_H
