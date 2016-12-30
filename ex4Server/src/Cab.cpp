//
// Created by nofar edan on 29/11/2016.
//

#include "Cab.h"

void Cab::move() {

}
/**
 *
 * @return num km
 */
double Cab::getNumKm() {
    return numKm;
}

/**
 *
 * @param id = cab id
 * @param manufactor = the manufactor
 * @param cabColor = cab color
 */
Cab::Cab(int id, char manufactor, char cabColor) {
    cabId = id;
    carManufactor = manufactor;
    color = cabColor;
    numKm = 0;
}

/**
 *
 * @return cab id.
 */
int Cab::getCabId() const {
    return cabId;
}
