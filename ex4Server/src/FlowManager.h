#ifndef EX2_FLOWMANAGER_H
#define EX2_FLOWMANAGER_H

#include "LuxuryCab.h"
#include "TaxiCenter.h"

class FlowManager {
private:
    TaxiCenter* taxiCenter;
    Map* map;
    GridNode*** arrGridNode;

public:
    FlowManager();
    ~FlowManager();
    void initializeMap();
    TaxiCenter* getTaxiCenter();
    void addDriver();
    void addTaxi();
    void addTrip();
    void startDriving();
    void getDriverPlace();
    };

#endif //EX2_FLOWMANAGER_H
