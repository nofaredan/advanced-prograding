#ifndef EX2_FLOWMANAGER_H
#define EX2_FLOWMANAGER_H

#include "LuxuryCab.h"
#include "TaxiCenter.h"
#include "Tcp.h"
#include "Map.h"
#include <pthread.h>

using namespace std;
using namespace boost::archive;
//std::stringstream ss;

class FlowManager {
private:
    static Map* map;
    static Tcp* tcp;
    static TaxiCenter* taxiCenter;
    GridNode*** arrGridNode;
    static int nWorldClock;
    static int numberOfDrivers;
    int nPort;
    static vector<pthread_t> vecTripThreads;
    static bool bMoveDrivers;
    static bool bKeepThreadAlive;
    static bool* bThreadsCalculating;
public:
    FlowManager(int port);
    ~FlowManager();
    void initializeMap();
    TaxiCenter* getTaxiCenter();
    void addDriver();
    void addTaxi();
    void addTrip();
    void getDriverPlace();
    bool isCalc();
    static void moveOneStep(Driver* driver, int socketNumber);
    void allowMoving();
    template <class Object>
    static void getSerializObject(Object **object, int socketNumber);
    template <class Object>
    static void sendSerializePrimitive(Object object, int socketNumber);
    template <class Object>
    static void sendSerializeObject(Object* obj, int socketNumer);
    static void* calculateBestRoute(void* trip);
    static void* handelThread(void* socketNumber);
    };

#endif //EX2_FLOWMANAGER_H
