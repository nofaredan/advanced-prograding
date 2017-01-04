#include "FlowManager.h"

/**
 * The constructor
 */
FlowManager::FlowManager() {
    taxiCenter = new TaxiCenter();
    nWorldClock = 0;
    udp = NULL;
}

/**
 * Add a new driver.
 * Get an input and add the driver to taxi center.
 */
void FlowManager::addDriver() {
    int numDrivers;
    cin >> numDrivers;
    for(int i=0; i<numDrivers; i++){

        // create new udp server -
        udp = new Udp(1, 5555);
        udp->initialize();

        Driver *driver;
        getSerializObject(&driver);

        // set socket udp id
        udp->setNID(driver->getId());

        driver->setMap(map);
        taxiCenter->addDriver(driver);

        sendSerializeObject(driver->getCab());
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
void FlowManager::getSerializObject(Object **object) {
    char buffer[4000];
    char* end = buffer + 3999;
    udp->reciveData(buffer, sizeof(buffer));

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

    //close udp
    if(udp != NULL) {
        //close udp -
        // send to client end of program
        sendSerializePrimitive(7);
        delete udp;
    }
}



template <class Object>
void FlowManager::sendSerializeObject(Object* obj){
    // serialize object-
    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << obj;
    s.flush();

    udp->sendData(serial_str);
}

template <class Object>
void FlowManager::sendSerializePrimitive(Object object){
    // serialize object-
    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << object;
    s.flush();

    udp->sendData(serial_str);
}

void FlowManager::moveOneStep() {
    // update the clock by one
    nWorldClock++;
    Trip* tMatchingTrip = taxiCenter->connectTripToDriver(nWorldClock);
    bool bTripOver = false;
    Driver* driver=  taxiCenter->getDriverById(udp->getNID());
    // if there's a new trip, sent to client the trip
    if (tMatchingTrip != NULL)
    {
        // sending new trip task to client
        sendSerializePrimitive(1);

        // send to client the trip
        sendSerializeObject(tMatchingTrip);

        // calc route -
        driver->calculateBestRoute();

        // move driver from first point
        bTripOver = driver->move();
    } // if driver has trip
    else if (driver->getHasTrip()){
        // sending new point task to client
        sendSerializePrimitive(2);

        // move driver
        bTripOver = driver->move();

        // get point from driver
        Point* point = new Point(driver->getCurrentPlace().getX(), taxiCenter->getDriverById(udp->getNID())->getCurrentPlace().getY());
        // send point to client
        sendSerializeObject(point);

        delete point;
    }

    // if trip is over, send it to client
    if (bTripOver){
        sendSerializePrimitive(3);

        // inform to taxi center that trip is over
        taxiCenter->endOfDriving(udp->getNID());
    }
}
