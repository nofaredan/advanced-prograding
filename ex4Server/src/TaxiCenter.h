//
// Created by rotem on 26/11/16.
//

#ifndef EX2_TEXICENTER_H
#define EX2_TEXICENTER_H

#include <iostream>
#include <vector>
#include <queue>
#include "Driver.h"
using namespace std;

class TaxiCenter {
private:
    queue<Driver*> drivers;
    vector<Cab*> availableCabs;
    queue<Driver*> busyDrivers;
    vector<Trip*> pendingTrip;

public:
    TaxiCenter();
    ~TaxiCenter();
    void addDriver(Driver* driver);
    void addCab(Cab* cab);
    void answerCall(Trip* trip);
    int getSizeAvailableCabs();
    int getSizeDrivers();
    void endOfDriving(int driverId);
    bool isDriving();
    void startDriving();
    Point getDriverPlace(int id);
    bool isTripExist(int id);
    bool isCabExist(int id);
    Point getDriverPlaceInQueue(queue<Driver*> driverQueue, int id);
    Trip* connectTripToDriver(int nClockTime, Driver* driver);
    Driver* getDriverById(int nDriverId);

private:
    void deleteQueueDrivers(queue<Driver*> queueDrivers);
    void deletePendingTrips(vector<Trip *> trips);
    void copyQueue(queue<Driver*>* queueDrivers, queue<Driver*>* anotherQueueDrivers);
    };


#endif //EX2_TEXICENTER_H
