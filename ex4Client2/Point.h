#ifndef EX1_POINT_H
#define EX1_POINT_H

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

/**
 * class point.
 */

class Point {
    friend class boost::serialization::access;
    template<class Archive>

    void serialize(Archive &ar, const unsigned int version){
        // attache to boost -

        ar & x;
        ar & y;
    }

private:
    int x, y;


public:
    Point() {};

    Point(int newX, int newY) : x(newX), y(newY) {};

    int getX();

    int getY();

    bool operator==(Point point);


};

#endif //EX1_POINT_H
