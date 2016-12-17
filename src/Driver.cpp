//
// Created by rotem on 26/11/16.
//

#include "Driver.h"


Driver::Driver(int driverId, int driverAge, char driverStatus, int experience, int taxiId, Map* mapDriver) {
    id = driverId;
    age = driverAge;
    driverStatus = status;
    yearsExperience = experience;
    cabId = taxiId;
    map = mapDriver;
    currentPlace = Point(0,0);
}

Cab Driver::getCab() {
    return cab;
}

int Driver::getCabId() {
    return cabId;
}

void Driver::setCab(Cab cab) {
    Driver::cab = cab;
}

void Driver::setCurrTrip(Trip* tripDriver) {
    currTrip = tripDriver;
}

void Driver::move (void (template  <class T>::*addto)(void)) {
    map->calculateBestRoute(currTrip->getCurrentPlace(), currTrip->getEnd());
    currTrip->setCurrentPlace(currTrip->getEnd());
    currentPlace = currTrip->getCurrentPlace();
    addto();
}

int Driver::getId() {
    return id;
}

Point Driver::getCurrentPlace() {
    return currentPlace;
}
