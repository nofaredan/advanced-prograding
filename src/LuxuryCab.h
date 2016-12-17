//
// Created by rotem on 26/11/16.
//

#ifndef EX2_LUXURYCAB_H
#define EX2_LUXURYCAB_H


#include "Cab.h"

class LuxuryCab: public Cab {
public:
    LuxuryCab(int id, char manufactor, char cabColor);
    void move();
};


#endif //EX2_LUXURYCAB_H
