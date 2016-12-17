#include "TaxiCenter.h"


TaxiCenter::TaxiCenter() {

}

void TaxiCenter::answerCall(Trip *trip) {
    queue<Driver> queueDrivers;
    while (drivers.size() > 0) {
        if (drivers.front().getCurrentPlace() == trip->getCurrentPlace()) {
            drivers.front().setCurrTrip(trip);
            busyDrivers.push(drivers.front());
        }
        queueDrivers.push(drivers.front());
        drivers.pop();
    }
    drivers = queueDrivers;
}

int TaxiCenter::getSizeAvailableCabs() {
    return (int) availableCabs.size();
}

int TaxiCenter::getSizeDrivers() {
    return (int) drivers.size();
}

void TaxiCenter::addDriver(Driver driver) {
    int i = 0;
    bool foundCab = false;
    while (i < availableCabs.size() && !foundCab) {
        if (driver.getCabId() == availableCabs[i].getCabId()) {
            driver.setCab(availableCabs[i]);
            foundCab = true;
        }
        i++;
    }
    drivers.push(driver);
}


void TaxiCenter::addCab(Cab cab) {
    queue<Driver> queueDrivers;
    while (drivers.size() > 0) {
        if (drivers.front().getCabId() == cab.getCabId()) {
            drivers.front().setCab(cab);
        }
        queueDrivers.push(drivers.front());
        drivers.pop();
    }
    availableCabs.push_back(cab);

}

void TaxiCenter::startDriving() {
    //queue<Driver> queueDrivers;
    while (busyDrivers.size() > 0) {
       // void(*method)(Driver*) = addToAvailableDrivers;
        //void* p =  &this->addToAvailableDrivers;
        busyDrivers.front().move(this->addToAvailableDrivers);
        ////// CHECK IF TO GET INTO BUSY DRIVERS OR NOT -
        //   busyDrivers.push(drivers.front());
     //   queueDrivers.push(busyDrivers.front());
        busyDrivers.pop();
    }
  //  busyDrivers = queueDrivers;
}

void TaxiCenter::addToAvailableDrivers(){
    //drivers.push(driver);
}

Point TaxiCenter::getDriverPlace(int id) {
    Point placeDrivers = getDriverPlaceInQueue(drivers,id);
    Point placeBusyDrivers = getDriverPlaceInQueue(busyDrivers, id);
    if(!(placeDrivers == Point(-1,-1))){
        return placeDrivers;
    }else {
        return placeBusyDrivers;
    }
}

Point TaxiCenter::getDriverPlaceInQueue(queue<Driver> driverQueue, int id){
    // look for the driver
    while (driverQueue.size() > 0) {
        if (driverQueue.front().getId() == id) {
          return driverQueue.front().getCurrentPlace();
        }
        driverQueue.pop();
    }
 return Point(-1,-1);
}
