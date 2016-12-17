#include <iostream>

#include "gtest/gtest.h"
#include "src/FlowManager.h"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    FlowManager flowManager = FlowManager();
    int userInput;

    flowManager.initializeMap();

    do {
        cin >> userInput;
        switch (userInput) {
            case 1:
                flowManager.addDriver();
                break;
            case 2:
                flowManager.addTrip();
                break;
            case 3:
                flowManager.addTaxi();
                break;
            case 4:
                flowManager.getDriverPlace();
                break;
            case 6:
                flowManager.startDriving();
                break;
            case 7:
                break;
            default:
                break;

        }
    } while (userInput != 7);


    return RUN_ALL_TESTS();
}