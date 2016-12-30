//
// Created by nofar edan on 29/11/2016.
//

#include "Trip.h"

/**
* C-TOR Trip
* @param id - trip id
* @param startPoint - trip stating Point
* @param endPoint - trip end Point
* @param passengers - passengers details
* @param tariffRide - tariff
**/
Trip::Trip(int id, Point startPoint, Point endPoint, int passengers, double tariffRide) {
    rideId = id;
    currentPlace = startPoint;
    end = endPoint;
    numPassengers = passengers;
    tariff = tariffRide;
    meterPassed = 0;
}

void Trip:: move(){

}

/*
* trip - getMeterPassed
@ return - func returns the meter passed value
*/
int Trip::getMeterPassed() {
    return meterPassed;
}

/*
* trip - addPassenger
* function adds Passenger to list
*/
void Trip::addPassenger() {

}

/*
* trip - getNumPassengers
* @return - func retruns num of passengers
*/
int Trip::getNumPassengers() {
    return numPassengers;
}

/*
* trip - getArrPassengers
* @return - func retruns passengers list
*/
vector<Passenger*> Trip::getArrPassengers() {
    return arrPassengers;
}

/*
* trip - getRideId
* @return - func retruns ride id
*/
int Trip::getRideId() {
    return rideId;
}

/*
* trip - getCurrentPlace
* @return - func retruns current trip place
*/
Point Trip::getCurrentPlace() {
    return currentPlace;
}

/*
* trip - getEnd
* @return - returns end point
*/
Point Trip::getEnd() {
    return end;
}

/*
* trip - getTariff
* @return - returns tariff
*/
double Trip::getTariff() {
    return tariff;
}

/*
* trip - setCurrentPlace
* function set currentPlace
*/
void Trip::setCurrentPlace(Point place) {
    currentPlace = place;
}