#include <iostream>
#include "FlowManager.h"

int main(int argc, char **argv) {

    int userInput;
    // a new flow manager:
    FlowManager* flowManager = new FlowManager();

    // initialize the map:
    flowManager->initializeMap();

    // get an input and go to the assignment accordingly:
    do {
        cin.clear();
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
            case 9:
                flowManager->moveOneStep();
                break;

            default:
                break;
        }



        } while (userInput != 7);

}