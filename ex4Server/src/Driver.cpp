//
// Created by rotem on 26/11/16.
//

#include "Driver.h"

/**
 * Driver constructor.
 * @param driverId = the driver's id
 * @param driverAge = the driver's age
 * @param driverStatus = driver's status
 * @param experience = the experience
 * @param taxiId = taxi id
 * @param mapDriver = driver's map
 */
Driver::Driver(int driverId, int driverAge, char driverStatus, int experience, int taxiId, Map *mapDriver) {
    id = driverId;
    age = driverAge;
    status = driverStatus;
    yearsExperience = experience;
    cabId = taxiId;
    map = mapDriver;
    currentPlace = Point(0, 0);
    currTrip = NULL;
    cab = NULL;
}

/**
 *
 * @return the driver's cab
 */
Cab *Driver::getCab() {
    return cab;
}

/**
 *
 * @return the cab id
 */
int Driver::getCabId() {
    return cabId;
}

/**
 *
 * @param cab = an another cab
 */
void Driver::setCab(Cab *cab) {
    Driver::cab = cab;
}

/**
 * set the current trip.
 * @param tripDriver = the trip.
 */
void Driver::setCurrTrip(Trip *tripDriver) {
    currTrip = tripDriver;
}

/**
 * move the driver.
 */
void Driver::calculateBestRoute() {
    // calculate route
    map->calculateBestRoute(currTrip->getCurrentPlace(), currTrip->getEnd());
}

/**
 * move the driver.
 * @return if trip over
 */
bool Driver::move() {
    // calculate route
    Point* currentPointNode = map->getPointOnRoad();

    // get the driver to the end point
    currTrip->setCurrentPlace(Point(currentPointNode->getX(), currentPointNode->getY()));
    currentPlace = currTrip->getCurrentPlace();

    // delete
    delete currentPointNode;
    //delete trip if the trip is over-
    if (currTrip->isTripOver()){
        delete currTrip;
        currTrip = NULL;
        return true;
    }

    return false;
}

/**
 *
 * @return driver id
 */
int Driver::getId() {
    return id;
}

/**
 *
 * @return the driver's current place
 */
Point Driver::getCurrentPlace() {
    return currentPlace;
}

/**
 * Driver distructor
 */
Driver::~Driver() {
    if (cab != NULL) {
        delete cab;
    }
    if (currTrip != NULL) {
        delete currTrip;
    }
}

bool Driver::getHasTrip() {
    return (currTrip != NULL);
}

void Driver::setMap(Map *map) {
    Driver::map = map;
}
