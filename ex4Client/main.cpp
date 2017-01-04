#include <iostream>
#include "Driver.h"
#include "Udp.h"

using namespace std;
using namespace boost::archive;
std::stringstream ss;


// create a udp connection -
Udp* udp = new Udp(0, 5555);


template <class Object>
void deSerializedObject(Object** object) {
    char buffer[4000];
    char *end = buffer + 3999;
    udp->reciveData(buffer, sizeof(buffer));

    boost::iostreams::basic_array_source<char> device(buffer, end);
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);

    ia >> *object;
}

void deSerializeTask(int* nTask) {
    char buffer[4000];
    char* end = buffer + 3999;
    udp->reciveData(buffer, sizeof(buffer));

    boost::iostreams::basic_array_source<char> device(buffer, end);
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);

    ia >> *nTask;
}

template <class Object>
void sendSerializeObject(Object* obj){
    // serialize object-
    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << obj;
    s.flush();

    udp->sendData(serial_str);
}

int main() {
    udp->initialize();

    // get a driver-
    int id, age, experience, cabId;
    char status, bufferInput;
    // get an input from the user:
    cin >> id >> bufferInput >> age >> bufferInput >> status >> bufferInput >> experience >> bufferInput >> cabId;

    // create new driver-
    Driver *driver = new Driver(id, age, status, experience, cabId);

    sendSerializeObject(driver);

    // get taxi from server-
    Cab* cab;
    deSerializedObject(&cab);

    driver->setCab(cab);

    Trip* trip = NULL;

    // get number of input
    int nTask;

    do{
        deSerializeTask(&nTask);

        switch (nTask){

            // new trip task -
            case 1:
                deSerializedObject(&trip);
                driver->setCurrTrip(trip);
                break;

            // move place
            case 2:
                // get point
                Point* newPoint;
                deSerializedObject(&newPoint);
                driver->move(newPoint);

                delete newPoint;
                break;

            // end of trip
            case 3:
                delete trip;
                driver->setCurrTrip(NULL);
                break;

        }
    }while (nTask != 7);

    // delete all -
    delete udp;
    delete driver;

    return 0;
}
