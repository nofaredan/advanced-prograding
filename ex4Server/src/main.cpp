#include <iostream>
#include "FlowManager.h"

int main(int argc, char **argv) {

    int userInput;
    // a new flow manager:
    FlowManager* flowManager = new FlowManager(atoi(argv[1]));

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
            case 7:
                delete flowManager;
                break;
            case 9:
                flowManager->allowMoving();
                break;

            default:
                std::cout << "-1" << std::endl;
                break;
        }

        } while (userInput != 7);

}