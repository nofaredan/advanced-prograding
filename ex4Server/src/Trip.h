//
// Created by nofar edan on 29/11/2016.
//

#ifndef EX2_TRIP_H
#define EX2_TRIP_H

#include "Point.h"
#include "Passenger.h"
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
    }
private:
    int rideId;
    int meterPassed;
    Point currentPlace;
    Point end;
    int numPassengers;
    double tariff;
    std::vector<Passenger*> arrPassengers;

public:
    Trip(){};
    Trip(int id, Point startPoint, Point endPoint, int passengers,double tariffRide);
    void move();
    void addPassenger();
    int getMeterPassed();
    int getNumPassengers();
    std::vector<Passenger*> getArrPassengers();
    int getRideId();
    Point getCurrentPlace();
    Point getEnd();
    double getTariff();
    void setCurrentPlace(Point place);
};

#endif //EX2_TRIP_H
