#include <iostream>
#include "CommunicationManager.h"
#include "FlowManager.h"
#include "Udp.h"
#include "boost/archive/text_oarchive.hpp"
#include "boost/serialization/vector.hpp"

using namespace boost::archive;

int main(int argc, char **argv) {


    while (1){
        // create new udp server -
        Udp udp(1, 5555);
        udp.initialize();

        char* buffer[1024];
        udp.reciveData(*buffer, sizeof(buffer));

        Driver *driver;
        //cout << buffer << endl;

        std::string serial_str = *buffer;
        boost::iostreams::basic_array_source<char> device(serial_str.c_str(), (serial_str.size()));
        boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
        boost::archive::binary_iarchive ia(s2);
        /*ia >> driver;

        std::cout << driver;
        */
        std::cout << "The client sent: " << buffer << std::endl;

        udp.sendData("world");
    }

    int userInput;
    // a new flow manager:
    /*FlowManager* flowManager = new FlowManager();

    // initialize the map:
    flowManager->initializeMap();

    // get an input and go to the assignment accordingly:
    do {
        cin >> userInput;
        switch (userInput) {
            case 1:
                flowManager->addDriver();
                break;
            case 2:
                flowManager->addTrip();
                break;
            case 3:
                flowManager->addTaxi();
                break;
            case 4:
                flowManager->getDriverPlace();
                break;
            case 6:
                flowManager->startDriving();
                break;
            case 7:
                delete flowManager;
                break;
            default:
                break;
        }
    } while (userInput != 7);*/
}