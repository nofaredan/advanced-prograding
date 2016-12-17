#include "FlowManager.h"


FlowManager::FlowManager() {
    taxiCenter = TaxiCenter();
}

void FlowManager::addDriver() {
    int id, age, experience, cabId;
    char status, buffer;
    cin >> id >> buffer >> age >> buffer >> status >> buffer >> experience >> buffer >> cabId;
    taxiCenter.addDriver(Driver(id, age, status, experience, cabId, map));
}

void FlowManager::addTaxi() {
    int id, taxiType;
    char manufactor, color, buffer;
    cin >> id >> buffer >> taxiType >> buffer >> manufactor >> buffer >> color;
    if (taxiType == 1) {
        taxiCenter.addCab(Cab(id, manufactor, color));
    } else {
        taxiCenter.addCab(LuxuryCab(id, manufactor, color));
    }
}

TaxiCenter FlowManager::getTaxiCenter() {
    return taxiCenter;
}

void FlowManager::addTrip() {
    int id, startX, startY, endX, endY, numPassengers;
    double tariff;
    char buffer;
    cin >> id >> buffer >> startX >> buffer >> startY >> buffer >>
        endX >> buffer >> endY >> buffer >> numPassengers >> buffer >> tariff;
    Trip* trip = new Trip(id, Point(startX,startY),Point(endX, endY),numPassengers, tariff);
    taxiCenter.answerCall(trip);
}

void FlowManager::startDriving(){
    taxiCenter.startDriving();
}

void FlowManager::initializeMap() {
    int numObstacles;
    char buffer;
    int x,y;
    int sizeX, sizeY;
    vector<Point> obstacles;

    // size grid
    cin >> sizeX >> sizeY;

    arrGridNode = new GridNode **[sizeY];
    cin >> numObstacles;
    for(int i=0; i<numObstacles; i++){
        cin >> x >> buffer >> y;
        obstacles.push_back(Point(x,y));
    }
    map = new Map(sizeX, sizeY, &obstacles, arrGridNode);
}

void FlowManager::getDriverPlace() {
    int driverId;
    Point currentPlace;
    cin >> driverId;
    currentPlace = taxiCenter.getDriverPlace(driverId);
    printf("(%d,%d)\n",currentPlace.getX(),currentPlace.getY());
}
