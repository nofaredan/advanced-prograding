//
// Created by nofar edan on 29/11/2016.
//

#ifndef EX2_PASSENGER_H
#define EX2_PASSENGER_H

#include "Point.h"

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
using namespace boost::archive;

class Passenger {

    friend class boost::serialization::access;
    template<class Archive>

    void serialize(Archive &ar, const unsigned int version){
        // attache to boost -

        ar & sourcePoint;
        ar & destinationPoint;
    }

private:
    Point sourcePoint;
    Point destinationPoint;

public:
    int randomScore();
};


#endif //EX2_PASSENGER_H
