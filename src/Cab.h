//
// Created by nofar edan on 29/11/2016.
//

#ifndef EX2_CAB_H
#define EX2_CAB_H

#include <string>
#include "Trip.h"

using namespace std;

class Cab {
private:

    int cabId;
    double minKm;
    char carManufactor;
    char color;
    double tariff;
    Trip trip;

public:
    Cab(){};
    Cab(int id, char manufactor, char cabColor);
    void move();
    double getMinKm();
    int getCabId() const;
};


#endif //EX2_CAB_H
