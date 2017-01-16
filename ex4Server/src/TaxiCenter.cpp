#include "TaxiCenter.h"


TaxiCenter::TaxiCenter() {

}

/*
* TaxiCenter::answerCall
* @param - trip
* function attach a trip to a driver according to
* trip and drivers place
*/
void TaxiCenter::answerCall(Trip *trip) {
    //queue<Driver *> queueDrivers;
    /*bool isMatchToDriver = false;
    while (drivers.size() > 0) {
        if (drivers.front()->getCurrentPlace() == trip->getCurrentPlace()
            && !(drivers.front()->getHasTrip())) {
            isMatchToDriver = true;
            drivers.front()->setCurrTrip(trip);
            busyDrivers.push(drivers.front());
        }else {
            queueDrivers.push(drivers.front());
        }
        drivers.pop();
    }
    copyQueue(&queueDrivers, &drivers);
    if (!isMatchToDriver) {*/
        pendingTrip.push_back(trip);
   // }
}

void TaxiCenter::copyQueue(queue<Driver*>* queueDrivers, queue<Driver*>* anotherQueueDrivers){
    *anotherQueueDrivers = *queueDrivers;
}

/*
* TaxiCenter::getSizeAvailableCabs
* @return - function returns available cabs amount
*/
int TaxiCenter::getSizeAvailableCabs() {
    return (int) availableCabs.size();
}

/*
* TaxiCenter::getSizeDrivers
* @return - function returns drivers amount
*/
int TaxiCenter::getSizeDrivers() {
    return (int) drivers.size();
}

/*
* TaxiCenter::addDriver
* @param - driver - driver to be added
* functions adds a driver to drivers list
*/
void TaxiCenter::addDriver(Driver *driver) {
    vector<Cab*> cabs;
    int i = 0;

    // add cab to driver
    while (i < availableCabs.size()) {
        if (driver->getCabId() == availableCabs[i]->getCabId() /*&&
            driver->getCab()!=NULL*/) {
            driver->setCab(availableCabs[i]);
        }else{
            cabs.push_back(availableCabs[i]);
        }
        i++;
    }
    drivers.push(driver);
    availableCabs = cabs;

    /*
    vector<Trip *> vectorTrips;
    while(pendingTrip.size()>0 && drivers.size()>0){
        if (driver->getCurrentPlace() == pendingTrip.front()->getCurrentPlace()
            && !(drivers.front()->getHasTrip())) {
            // if found trip - connect it to driver
            driver->setCurrTrip(pendingTrip.front());
            busyDrivers.push(drivers.front());
            drivers.pop();
        }else{
            vectorTrips.push_back(pendingTrip.front());
        }
        pendingTrip.pop_back();
    }
    pendingTrip = vectorTrips;*/

}
/*
* TaxiCenter::addCab
* @param - cab - cab to be added
* functions adds a cab to driver according to id
*/
void TaxiCenter::addCab(Cab *cab) {
    queue<Driver *> queueDrivers;
    while (drivers.size() > 0) {
        if (drivers.front()->getCabId() == cab->getCabId()) {
            drivers.front()->setCab(cab);
        }
        queueDrivers.push(drivers.front());
        drivers.pop();
    }
    drivers = queueDrivers;
    availableCabs.push_back(cab);
}

void TaxiCenter::endOfDriving(int driverId){
    queue<Driver *> queueBusyDrivers;

    // find driver
    while (busyDrivers.size() > 0){
        if (busyDrivers.front()->getId() == driverId){
            // add to drivers
            drivers.push(busyDrivers.front());

        }
        else{
            queueBusyDrivers.push(busyDrivers.front());
        }

        busyDrivers.pop();
    }

    copyQueue(&queueBusyDrivers, &busyDrivers);
}

/*
* TaxiCenter::getDriverPlace
* @return driver place according to id
*/
Point TaxiCenter::getDriverPlace(int id) {
    Point placeDrivers = getDriverPlaceInQueue(drivers, id);
    Point placeBusyDrivers = getDriverPlaceInQueue(busyDrivers, id);
    if (!(placeDrivers == Point(-1, -1))) {
        return placeDrivers;
    } else {
        return placeBusyDrivers;
    }
}

/*
* TaxiCenter::getDriverPlaceInQueue
* @return driver place in queue
*/
Point TaxiCenter::getDriverPlaceInQueue(queue<Driver *> driverQueue, int id) {
// look for the driver
while (driverQueue.size() > 0) {
    if (driverQueue.front()->getId() == id) {
    return driverQueue.front()->getCurrentPlace();
    }
    driverQueue.pop();
}
    return Point(-1, -1);
}

/*
* TaxiCenter::~TaxiCenter
* taxi center d-tor
*/
TaxiCenter::~TaxiCenter() {
    deleteQueueDrivers(drivers);
    deleteQueueDrivers(busyDrivers);
    deletePendingTrips(pendingTrip);

    for (int i = 0; i < availableCabs.size(); i++) {
        delete availableCabs[i];
    }
}

/*
* TaxiCenter::deleteQueueDrivers
* @param - queueDrivers
* function delete all drivres
*/
void TaxiCenter::deleteQueueDrivers(queue<Driver *> queueDrivers) {
    while (queueDrivers.size() > 0) {
        delete queueDrivers.front();
        queueDrivers.pop();
    }
}

/*
* TaxiCenter::deletePendingTrips
* @param - trips
* function delete all pending trips
*/
void TaxiCenter::deletePendingTrips(vector<Trip *> trips) {
    for (int i = 0; i < trips.size(); i++) {
        delete trips[i];
    }
}

bool TaxiCenter::isDriving(){
    queue<Driver *> queueDrivers;
    queue<Driver *> queueBusyDrivers;

    bool isDriving = false;

    // pop driver from drivers
    while (drivers.size() > 0) {
        if (drivers.front()->isIsDriving()) {
            isDriving = true;
        }
        queueDrivers.push(drivers.front());
        drivers.pop();
    }


    // find driver
    while (busyDrivers.size() > 0){
        if (busyDrivers.front()->isIsDriving()){
            isDriving = true;

        }
        queueBusyDrivers.push(busyDrivers.front());
        busyDrivers.pop();
    }

    if (queueBusyDrivers.size() > 0){
        copyQueue(&queueBusyDrivers, &busyDrivers);
    }

    if (queueDrivers.size() > 0){
        copyQueue(&queueDrivers, &drivers);
    }

    return isDriving;
}

void TaxiCenter::startDriving(){
    queue<Driver *> queueDrivers;
    queue<Driver *> queueBusyDrivers;

    // pop driver from drivers
    while (drivers.size() > 0) {
        drivers.front()->setIsDriving(true);
        queueDrivers.push(drivers.front());
        drivers.pop();
    }


    // pop driver from drivers
    while (busyDrivers.size() > 0) {
        busyDrivers.front()->setIsDriving(true);
        queueBusyDrivers.push(busyDrivers.front());
        busyDrivers.pop();
    }

    if (queueBusyDrivers.size() > 0){
        copyQueue(&queueBusyDrivers, &busyDrivers);
    }

    if (queueDrivers.size() > 0){
        copyQueue(&queueDrivers, &drivers);
    }

}

Trip* TaxiCenter::connectTripToDriver(int nClockTime, Driver* driver) {
    // go over each trip, and attach to driver
    // the suitable trip -
    vector<Trip *> vectorTrips;
    queue<Driver *> queueDrivers;
    Trip* matchingTrip = NULL;

    while (pendingTrip.size() > 0) {
        // if driver has no trip,
        // same place of trip, and it's trip time by clock
        if (driver->getCurrentPlace() == pendingTrip.back()->getCurrentPlace()
            && !(driver->getHasTrip()) && pendingTrip.back()->getNTimeOfStart() == nClockTime) {
            driver->setCurrTrip(pendingTrip.back());
            // pop driver from drivers
            while (drivers.size() > 0) {
                if (drivers.front()->getId() == driver->getId()) {
                    busyDrivers.push(drivers.front());
                } else {
                    queueDrivers.push(drivers.front());
                }
                drivers.pop();
            }
            matchingTrip = pendingTrip.back();
        } else {
            vectorTrips.push_back(pendingTrip.back());
        }

        pendingTrip.pop_back();
    }

   if (queueDrivers.size() > 0){
        copyQueue(&queueDrivers, &drivers);
    }

    if (vectorTrips.size() > 0){
        pendingTrip = vectorTrips;
    }

    return matchingTrip;
}

Driver* TaxiCenter::getDriverById(int nDriverId) {
    Driver* driver;
    queue<Driver *> queueDrivers;
    queue<Driver *> queueBusyDrivers;

    // find driver - busy / available
    while (drivers.size() > 0){
        if (drivers.front()->getId() == nDriverId){
            driver = drivers.front();
        }

        queueDrivers.push(drivers.front());
        drivers.pop();
    }

    copyQueue(&queueDrivers, &drivers);
    while (busyDrivers.size() > 0){
        if (busyDrivers.front()->getId() == nDriverId){
            driver = busyDrivers.front();
        }

        queueBusyDrivers.push(busyDrivers.front());
        busyDrivers.pop();
    }

    copyQueue(&queueBusyDrivers, &busyDrivers);
    return driver;
}
