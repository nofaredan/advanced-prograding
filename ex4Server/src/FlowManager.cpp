#include "FlowManager.h"

Map* FlowManager::map;
Tcp* FlowManager::tcp;
TaxiCenter* FlowManager::taxiCenter;
bool FlowManager::bMoveDrivers;
vector<pthread_t> FlowManager::vecTripThreads;
int FlowManager::nWorldClock;
int FlowManager::numberOfDrivers;
bool FlowManager::bKeepThreadAlive;
bool* FlowManager::bThreadsCalculating;

pthread_mutex_t count_mutex_flow_manager     = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t count_mutex_moving           = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t count_mutex     = PTHREAD_MUTEX_INITIALIZER;

/**
 * The constructor
 */
FlowManager::FlowManager(int port) {
    taxiCenter = new TaxiCenter();
    nWorldClock = 0;
    tcp = NULL;
    nPort = port;
    bMoveDrivers = false;
    bKeepThreadAlive = false;
}

/**
 * Add a new driver.
 * Get an input and add the driver to taxi center.
 */
void FlowManager::addDriver() {
    int numDrivers;
    cin >> numDrivers;

        // create new tcp server -
        tcp = new Tcp(1, nPort);
        tcp->initialize();
        bThreadsCalculating  = new bool[numDrivers];
        numberOfDrivers = numDrivers;
        // for each driver, set that the driver is calculating
        for (int i = 0; i < numDrivers; i++){
            bThreadsCalculating[i] = true;
        }
        // set connection for each driver - create threads.
        tcp->setConnection(numDrivers, handelThread);
    }

/**
* the treads are created and sent here.
**/
void* FlowManager::handelThread(void* params){
    int nTask;
    int socketNum = ((int*)params)[0];
    int placeInArray = ((int*)params)[1];
    delete (int*)params;

    pthread_mutex_lock(&count_mutex_flow_manager);

    // get driver and send it
    Driver *driver;
    getSerializObject(&driver, socketNum);

    taxiCenter->addDriver(driver);

    sendSerializeObject(driver->getCab(), socketNum);

    pthread_mutex_unlock(&count_mutex_flow_manager);
    // while not moving-
    bThreadsCalculating[placeInArray] = false;
    bKeepThreadAlive = true;
    while (bKeepThreadAlive){
        //if (bMoveDrivers){
        if (driver->isIsDriving()){
            // lock!
            pthread_mutex_lock(&count_mutex_moving);

            // move only if trip finished it's calculations
            for(int i = 0; i < vecTripThreads.size(); i++)
            {
                pthread_join((vecTripThreads.at(i)), NULL);
            }

            moveOneStep(driver, socketNum);

            pthread_mutex_unlock(&count_mutex_moving);

            driver->setIsDriving(false);
        }
   }

    //close tcp for each client
    if(tcp != NULL) {
        //close tcp -
        // send to client end of program
        sendSerializePrimitive(7, socketNum);
    }
}

/**
 * add a taxi
 */
void FlowManager::addTaxi() {
    int id, taxiType;
    char manufactor, color, buffer;
    // get an input from the user
    cin >> id >> buffer >> taxiType >> buffer >> manufactor >> buffer >> color;

    // create a taxi according to the input
    if (taxiType == 1) {
        taxiCenter->addCab(new Cab(id, manufactor, color));
    } else {
        taxiCenter->addCab(new LuxuryCab(id, manufactor, color));
    }
}

/**
* Get serialize object
**/
template <class Object>
void FlowManager::getSerializObject(Object **object, int socketNumber) {
    char buffer[1600001];
    char* end = buffer + 1600000;
    tcp->reciveData(buffer, sizeof(buffer), socketNumber);

    boost::iostreams::basic_array_source<char> device(buffer, end);
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);

    ia >> *object;
}


/**
 *
 * @return the taxi center
 */
TaxiCenter *FlowManager::getTaxiCenter() {
    return taxiCenter;
}

/**
 * add a trip
 */
void FlowManager::addTrip() {
    int id, startX, startY, endX, endY, numPassengers, timeOfStart;
    double tariff;
    char buffer;
    // get an input from the user:
    cin >> id >> buffer >> startX >> buffer >> startY >> buffer >>
        endX >> buffer >> endY >> buffer >> numPassengers >> buffer >> tariff >> buffer >> timeOfStart;
    // create a new trip
    Trip *trip = new Trip(id, Point(startX, startY), Point(endX, endY), numPassengers, tariff, timeOfStart);
    // send the trip to taxi center
    taxiCenter->answerCall(trip);

    pthread_t thread;

    // handel thread
    pthread_create(&thread, NULL, calculateBestRoute,  (void *) trip);

    vecTripThreads.push_back(thread);
}

/**
 * calculate best route for trip.
 */
void* FlowManager::calculateBestRoute(void* trip) {
    pthread_mutex_lock(&count_mutex);

    Trip* currTrip = (Trip*) trip;
    // calculate route
    currTrip->setRodePoints(map->calculateBestRoute(currTrip->getCurrentPlace(), currTrip->getEnd()));

    pthread_mutex_unlock(&count_mutex);

    return NULL;
}


/**
 * initialize the map.
 */
void FlowManager::initializeMap() {
    int numObstacles;
    char buffer;
    int x, y;
    int sizeX, sizeY;
    vector<Point> obstacles;

    // size grid
    cin >> sizeX >> sizeY;

    // create a grid node array
    arrGridNode = new GridNode **[sizeY];

    // get the number of obstacles
    cin >> numObstacles;
    // get the obstacles
    for (int i = 0; i < numObstacles; i++) {
        cin >> x >> buffer >> y;
        obstacles.push_back(Point(x, y));
    }

    // create a new map
    map = new Map(sizeX, sizeY, &obstacles, arrGridNode);
}

/**
 * Get the driver's place
 */
void FlowManager::getDriverPlace() {
    int driverId;
    Point currentPlace;
    // get the driver's id
    cin >> driverId;
    // get the current place of the driver
    currentPlace = taxiCenter->getDriverPlace(driverId);
    // print the current place of the driver:
    printf("(%d,%d)\n", currentPlace.getX(), currentPlace.getY());
}

/**
 * destructor.
 */
FlowManager::~FlowManager() {
    // delete map
    if(map != NULL) {
        delete map;
    }
    // delete taxi center
    if(taxiCenter != NULL) {
        delete taxiCenter;
    }
    // step keeping threads alive - killing the threads
    bKeepThreadAlive = false;

    // stop connecing with the clients - stop tcp
    if(tcp != NULL) {
        tcp->joinThreads();
        delete tcp;
    }
}


/**
* send serialize object to the client
**/
template <class Object>
void FlowManager::sendSerializeObject(Object* obj, int socketNumber){
    // serialize object-
    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << obj;
    s.flush();

    // send the data to the client
    tcp->sendData(serial_str, socketNumber);
}


/**
* send the serialize primitive to the client
**/
template <class Object>
void FlowManager::sendSerializePrimitive(Object object, int socketNumber){
    // serialize object-
    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << object;
    s.flush();

    // send the data to the client
    tcp->sendData(serial_str, socketNumber);
}

/**
* start moving - when press on 9, the driver needs to move
* if the trip's clock equals to the world clock
**/
void FlowManager::allowMoving(){
    while( isCalc() )
    {
        // wait
    }

    // update the clock by one
    nWorldClock++;

    bMoveDrivers = true;

    // call to all drivers to move!-
    taxiCenter->startDriving();

    // while drivers are driving
    while ((bMoveDrivers) || (taxiCenter->isDriving()) ){
        // wait
    }

    bMoveDrivers = false;
}

/**
* returns if the threads are in the middle of calculation
**/
bool FlowManager::isCalc(){
    for (int i = 0; i < numberOfDrivers; i++){
        if (bThreadsCalculating[i]){
            return true;
        }
    }
    return false;
}

/**
* move one step - the driver moves one step on the grid.
**/
void FlowManager::moveOneStep(Driver* driver, int socketNumber) {
    bMoveDrivers = true;

    Trip* tMatchingTrip = taxiCenter->connectTripToDriver(nWorldClock, driver);

    bool bTripOver = false;

    // if there's a new trip, sent to client the trip
    if (tMatchingTrip != NULL)
    {
        // sending new trip task to client
        sendSerializePrimitive(1, socketNumber);

        // send to client the trip
        sendSerializeObject(tMatchingTrip, socketNumber);

        // move driver from first point
        bTripOver = driver->move();

    } // if driver has trip
    else if (driver->getHasTrip()){
        // sending new point task to client
        sendSerializePrimitive(2, socketNumber);

        // move driver
        bTripOver = driver->move();

        // get point from driver
        Point* point = new Point(driver->getCurrentPlace().getX(),
                                 driver->getCurrentPlace().getY());

        // send point to client
        sendSerializeObject(point, socketNumber);

        delete point;
    }
    // if trip is over, send it to client
    if (bTripOver){
        sendSerializePrimitive(3, socketNumber);

        // inform to taxi center that trip is over
        taxiCenter->endOfDriving(driver->getId());
    }
    bMoveDrivers = false;
}
