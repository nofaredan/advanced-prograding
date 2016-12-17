//
// Created by nofar edan on 29/11/2016.
//

#include "Trip.h"


Trip::Trip(int id, Point startPoint, Point endPoint, int passengers, double tariffRide) {
    rideId = id;
    currentPlace = startPoint;
    end = endPoint;
    numPassengers = passengers;
    tariff = tariffRide;
}

void Trip:: move(){

}

int Trip::getMeterPassed() {
    return meterPassed;
}

void Trip::addPassenger() {

}

int Trip::getNumPassengers() {
    return numPassengers;
}

vector<Passenger*> Trip::getArrPassengers() {
    return arrPassengers;
}

int Trip::getRideId() {
    return rideId;
}

Point Trip::getCurrentPlace() {
    return currentPlace;
}

Point Trip::getEnd() {
    return end;
}

double Trip::getTariff() {
    return tariff;
}

void Trip::setCurrentPlace(Point place) {
    currentPlace = place;
}

