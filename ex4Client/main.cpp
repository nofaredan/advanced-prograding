#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "Driver.h"
#include "Udp.h"

using namespace std;
std::stringstream ss;


int main() {
    Udp udp(0, 5555);
    udp.initialize();

    // get a driver-
    int id, age, experience, cabId;
    char status, bufferInput;
    // get an input from the user:
    cin >> id >> bufferInput >> age >> bufferInput >> status >> bufferInput >> experience >> bufferInput >> cabId;

    // create new driver-
    Driver *driver = new Driver(id, age, status, experience, cabId);

    // serialize driver-
    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << driver;
    s.flush();

    cout << serial_str << endl;

    udp.sendData(serial_str);
    udp.sendData("Hello");

    char buffer[1024];
    udp.reciveData(buffer, sizeof(buffer));

    cout << buffer << endl;

    return 0;
}