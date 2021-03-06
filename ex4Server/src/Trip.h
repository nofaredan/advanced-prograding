//
// Created by nofar edan on 29/11/2016.
//

#ifndef EX2_TRIP_H
#define EX2_TRIP_H

#include "Point.h"
#include "Passenger.h"
#include <stack>
#include <vector>
#include <fstream>
#include <sstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/vector.hpp>
using namespace boost::archive;

class Trip {

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version){
        // attache to boost -
        ar & rideId;
        ar & meterPassed;
        ar & currentPlace;
        ar & end;
        ar & numPassengers;
        ar & tariff;
        ar & arrPassengers;
        ar & nTimeOfStart;
    }
private:
    int rideId;
    int meterPassed;
    Point currentPlace;
    Point end;
    int numPassengers;
    int nTimeOfStart;
    std::stack<Point*> *rodePoints;
public:
    std::stack<Point *, std::deque<Point *, std::allocator<Point *>>> *getRodePoints() const;

    void setRodePoints(std::stack<Point *, std::deque<Point *, std::allocator<Point *>>> *rodePoints);

public:
    int getNTimeOfStart() const;

private:
    double tariff;
    std::vector<Passenger*> arrPassengers;

public:
    Trip(){};
    ~Trip();
    Trip(int id, Point startPoint, Point endPoint, int passengers,double tariffRide, int timeOfStart);
    void move();
    void addPassenger();
    int getMeterPassed();
    int getNumPassengers();
    std::vector<Passenger*> getArrPassengers();
    int getRideId();
    Point getCurrentPlace();
    Point getEnd();
    Point* getPointOnRoad();
    bool isTripOver();
    double getTariff();
    void setCurrentPlace(Point place);
};

#endif //EX2_TRIP_H
