//
// Created by nofar edan on 29/11/2016.
//

#include "Cab.h"

void Cab::move() {

}

double Cab::getMinKm() {
    return minKm;
}

Cab::Cab(int id, char manufactor, char cabColor) {
    cabId = id;
    carManufactor = manufactor;
    color = cabColor;
}

int Cab::getCabId() const {
    return cabId;
}
