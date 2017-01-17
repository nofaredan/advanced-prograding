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
   // for(int i=0; i<numDrivers; i++){

        // create new tcp server -
        tcp = new Tcp(1, nPort);
        tcp->initialize();
        bThreadsCalculating  = new bool[numDrivers];
        numberOfDrivers = numDrivers;
        for (int i = 0; i < numDrivers; i++){
            bThreadsCalculating[i] = true;
        }
        tcp->setConnection(numDrivers, handelThread);

    //}
}

void* FlowManager::handelThread(void* params){
    int nTask;
    int socketNum = ((int*)params)[0];
    int placeInArray = ((int*)params)[1];
    delete (int*)params;

    //bThreadsCalculating[placeInArray] = true;

    pthread_mutex_lock(&count_mutex_flow_manager);

    // get driver and send it
    Driver *driver;
    getSerializObject(&driver, socketNum);


    // set socket tcp id
    //tcp->setNID(driver->getId());

   // driver->setMap(map);
    taxiCenter->addDriver(driver);


    sendSerializeObject(driver->getCab(), socketNum);


    pthread_mutex_unlock(&count_mutex_flow_manager);
    // while not moving-
    bThreadsCalculating[placeInArray] = false;
    bKeepThreadAlive = true;
    cout << "handelThread 4 " << driver->getId() << endl;
    while (bKeepThreadAlive){
        //if (bMoveDrivers){
        if (driver->isIsDriving()){
            cout << "handelThread 5 " << driver->getId() << endl;
            // lock!
            pthread_mutex_lock(&count_mutex_moving);

           // driver->setIsDriving(true);
            // move only if trip finished it's calculations
            for(int i = 0; i < vecTripThreads.size(); i++)
            {
                //pthread_t thread = *(vecTripThreads.at(i));

                pthread_join((vecTripThreads.at(i)), NULL);
            }

            moveOneStep(driver, socketNum);

            pthread_mutex_unlock(&count_mutex_moving);

            cout << "handelThread 6 " << driver->getId() << endl;
            driver->setIsDriving(false);
            cout << "handelThread 7 " << driver->getId() << endl;
           // bMoveDrivers = false;
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


template <class Object>
void FlowManager::getSerializObject(Object **object, int socketNumber) {
    char buffer[131072];
    char* end = buffer + 131071;
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
    cout << "calculateBestRoute 1 " << ((Trip*)(trip))->getRideId() << endl;

    pthread_mutex_lock(&count_mutex);

    Trip* currTrip = (Trip*) trip;
    // calculate route
    currTrip->setRodePoints(map->calculateBestRoute(currTrip->getCurrentPlace(), currTrip->getEnd()));

    pthread_mutex_unlock(&count_mutex);

    cout << "calculateBestRoute 2 " << ((Trip*)(trip))->getRideId() << endl;

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
    if(map != NULL) {
        delete map;
    }
    if(taxiCenter != NULL) {
        delete taxiCenter;
    }

    bKeepThreadAlive = false;

    if(tcp != NULL) {
        tcp->joinThreads();
        delete tcp;
    }
}



template <class Object>
void FlowManager::sendSerializeObject(Object* obj, int socketNumber){
    // serialize object-
    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << obj;
    s.flush();

    tcp->sendData(serial_str, socketNumber);
}

template <class Object>
void FlowManager::sendSerializePrimitive(Object object, int socketNumber){
    // serialize object-
    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << object;
    s.flush();

    tcp->sendData(serial_str, socketNumber);
}

void FlowManager::allowMoving(){
    cout << "taxiCenter->isDriving() 0 " << endl;
    while( isCalc() )
    {
        // wait
    }

    cout << "taxiCenter->isDriving() 1 " << endl;

    // update the clock by one
    nWorldClock++;

    bMoveDrivers = true;

    cout << "taxiCenter->isDriving() 2 " << endl;

    // call to all drivers to move!-
    taxiCenter->startDriving();

    // while drivers are driving
    while ((bMoveDrivers) || (taxiCenter->isDriving()) ){
        // wait
    }

    cout << "taxiCenter->isDriving() 3 " << taxiCenter->isDriving() << endl;

    bMoveDrivers = false;

    cout << "taxiCenter->isDriving() 4 " << taxiCenter->isDriving() << endl;
}

bool FlowManager::isCalc(){
    for (int i = 0; i < numberOfDrivers; i++){
        //cout << "bThreadsCalculating[i] " << bThreadsCalculating[i] << endl;
        if (bThreadsCalculating[i]){
            return true;
        }
    }

    return false;
}

void FlowManager::moveOneStep(Driver* driver, int socketNumber) {
    bMoveDrivers = true;

    cout << "moveOneStep driver->getID() " << driver->getId() << endl;
    cout << "moveOneStep nWorldClock " << nWorldClock << endl;

    Trip* tMatchingTrip = taxiCenter->connectTripToDriver(nWorldClock, driver);

    cout << "tMatchingTrip " << tMatchingTrip << endl;

    cout << "driver->getHasTrip() " << driver->getHasTrip() << endl;

    bool bTripOver = false;
    //Driver* driver=  taxiCenter->getDriverById(tcp->getNID());
    // if there's a new trip, sent to client the trip
    if (tMatchingTrip != NULL)
    {
        cout << "tMatchingTrip->getEnd() " << tMatchingTrip->getEnd().getX() << tMatchingTrip->getEnd().getY()<< endl;

        // sending new trip task to client
        sendSerializePrimitive(1, socketNumber);

        cout << "moveOneStep 31 " << endl;

        // send to client the trip
        sendSerializeObject(tMatchingTrip, socketNumber);

        cout << "moveOneStep 32 " << endl;
        // calc route -
       // driver->calculateBestRoute();

        // move driver from first point
        bTripOver = driver->move();

        cout << "moveOneStep 3 " << endl;
    } // if driver has trip
    else if (driver->getHasTrip()){
        cout << "moveOneStep 4 " << endl;
        // sending new point task to client
        sendSerializePrimitive(2, socketNumber);

        cout << "moveOneStep 41 " << endl;
        // move driver
        bTripOver = driver->move();

        cout << "moveOneStep 42 " << endl;

        // get point from driver
        Point* point = new Point(driver->getCurrentPlace().getX(),
                                 driver->getCurrentPlace().getY());

        cout << "driver->getCurrentPlace() " << driver->getCurrentPlace().getX() <<  driver->getCurrentPlace().getY() << endl;

        // send point to client
        sendSerializeObject(point, socketNumber);

        cout << "moveOneStep 5 " << endl;

        delete point;
    }

    cout << "moveOneStep 6 " << endl;
    // if trip is over, send it to client
    if (bTripOver){
        cout << "moveOneStep 7 " << endl;
        sendSerializePrimitive(3, socketNumber);

        cout << "moveOneStep 8 " << endl;

        // inform to taxi center that trip is over
        taxiCenter->endOfDriving(driver->getId());
    }

    cout << "moveOneStep 9 " << endl;

    bMoveDrivers = false;
}
