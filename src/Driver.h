//
// Created by rotem on 26/11/16.
//

#ifndef EX2_DRIVER_H
#define EX2_DRIVER_H

#include <iostream>
#include "Cab.h"
#include "Trip.h"
#include "Statistics.h"
#include <string>
#include "Map.h"
using namespace std;

class Driver {
private:
    int id;
    int age;
    char status;
    int yearsExperience;
    int avgSatisfaction;
    Cab cab;
    int cabId;
    int satisfaction;
    int customers;
    Trip* currTrip;
    //Statistics statistics[];
    Map* map;
    Point currentPlace;

public:
    Driver(){};
    Driver(int driverId, int driverAge, char driverStatus,int experience,
           int taxiId, Map* mapDriver);
    Cab getCab();
    int getCabId();
    void setCab(Cab cab);
    void setCurrTrip(Trip* tripDriver);
    void move (void (template  <class T>::*addto)(void));
    int getId();
    Point getCurrentPlace();
};


#endif //EX2_DRIVER_H
