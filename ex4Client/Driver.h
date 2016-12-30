
#ifndef EX2_DRIVER_H
#define EX2_DRIVER_H

#include <iostream>
#include "Cab.h"
#include "Trip.h"
#include <string>
using namespace std;

class Driver {
private:
    int id;
    int age;
    char status;
    int yearsExperience;
    int avgSatisfaction;
    Cab* cab;
    int cabId;
    int satisfaction;
    int customers;
    Trip* currTrip;
    Point currentPlace;

public:
    Driver(){};
    Driver(int driverId, int driverAge, char driverStatus,int experience,
           int taxiId);
    ~Driver();
    Cab* getCab();
    int getCabId();
    void setCab(Cab* cab);
    void setCurrTrip(Trip* tripDriver);
    void move(Point newPlace);
    int getId();
    Point getCurrentPlace();
    bool getHasTrip();
};


#endif //EX2_DRIVER_H
