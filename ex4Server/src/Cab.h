//
// Created by nofar edan on 29/11/2016.
//

#ifndef EX2_CAB_H
#define EX2_CAB_H

#include <string>
#include "Trip.h"

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


class Cab {

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version){
        // attache to boost -

        ar & cabId;
        ar & numKm;
        ar & carManufactor;
        ar & color;
        ar & tariff;
    }
private:
    int cabId;
    double numKm;
    char carManufactor;
    char color;
    double tariff;

public:
    Cab(){};
    Cab(int id, char manufactor, char cabColor);
    void move();
    double getNumKm();
    int getCabId() const;
};


#endif //EX2_CAB_H
