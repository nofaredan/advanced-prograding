#include <iostream>
#include "Driver.h"
#include "Udp.h"

using namespace std;
using namespace boost::archive;
std::stringstream ss;

// create a udp connection -
Udp udp(0, 5555);

void getSerializedCab(Cab** cab) {
    char buffer[4000];
    char* end = buffer + 3999;
    udp.reciveData(buffer, sizeof(buffer));

    boost::iostreams::basic_array_source<char> device(buffer, end);
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);

    ia >> *cab;
}

void getSerializedTrip(Trip** cab) {
    char buffer[4000];
    char* end = buffer + 3999;
    udp.reciveData(buffer, sizeof(buffer));

    boost::iostreams::basic_array_source<char> device(buffer, end);
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);

    ia >> *trip;
}

void sendSerializeDriver(Driver* driver){
    // serialize object-
    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << driver;
    s.flush();

    udp.sendData(serial_str);
}

int main() {
    udp.initialize();

    // get a driver-
    int id, age, experience, cabId;
    char status, bufferInput;
    // get an input from the user:
    cin >> id >> bufferInput >> age >> bufferInput >> status >> bufferInput >> experience >> bufferInput >> cabId;

    // create new driver-
    Driver *driver = new Driver(id, age, status, experience, cabId);

    sendSerializeDriver(driver);

    // get taxi from server-
    Cab* cab;
    getSerializedCab(&cab);

    driver->setCab(cab);

    Trip* trip;
    getSerializedTrip(&trip);

    return 0;
}
