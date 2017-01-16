#include <iostream>
#include "Driver.h"
#include "Tcp.h"

using namespace std;
using namespace boost::archive;
std::stringstream ss;


// create a tcp connection -
Tcp* tcp;


template <class Object>
void deSerializedObject(Object** object) {
    char buffer[131072];
    char *end = buffer + 131071;
    tcp->reciveData(buffer, sizeof(buffer));

    boost::iostreams::basic_array_source<char> device(buffer, end);
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);

    ia >> *object;
}

template <class Object>
void sendSerializePrimitive(Object object){
    // serialize object-
    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << object;
    s.flush();

    tcp->sendData(serial_str);
}

void deSerializeTask(int* nTask) {
    char buffer[131072];
    char* end = buffer + 131071;
    tcp->reciveData(buffer, sizeof(buffer));

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

    tcp->sendData(serial_str);
}

int main(int argc, char **argv) {
    tcp = new Tcp(0, atoi(argv[2]));
    tcp->initialize();

    // get a driver-
    int id, age, experience, cabId;
    char status, bufferInput;
    // get an input from the user:
    cin >> id >> bufferInput >> age >> bufferInput >> status >> bufferInput >> experience >> bufferInput >> cabId;

    // create new driver-
    Driver *driver = new Driver(id, age, status, experience, cabId);

    // if server asked for a driver-
    sendSerializeObject(driver);

    // get taxi from server-
    Cab* cab = NULL;
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
    delete tcp;
    delete driver;

    return 0;
}
