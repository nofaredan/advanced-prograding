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
    int nWorldClock;
    Udp* udp;

public:
    FlowManager();
    ~FlowManager();
    void initializeMap();
    TaxiCenter* getTaxiCenter();
    void addDriver();
    void addTaxi();
    void addTrip();
    void getDriverPlace();
    void moveOneStep();
    template <class Object>
    void getSerializObject(Object **object);
    template <class Object>
    void sendSerializePrimitive(Object object);
    template <class Object>
    void sendSerializeObject(Object* obj);
    };

#endif //EX2_FLOWMANAGER_H
