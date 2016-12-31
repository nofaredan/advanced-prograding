#ifndef EX2_FLOWMANAGER_H
#define EX2_FLOWMANAGER_H

#include "LuxuryCab.h"
#include "TaxiCenter.h"
#include "Udp.h"

using namespace std;
using namespace boost::archive;
//std::stringstream ss;

class FlowManager {
private:
    TaxiCenter* taxiCenter;
    Map* map;
    GridNode*** arrGridNode;
    int nWorldClock = 0;
    Udp udp;

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
    void moveOneStep();
    void sendSerializeTaxi(Cab* cab);
    void getSerializedDriver(Driver** driver);
    };

#endif //EX2_FLOWMANAGER_H
