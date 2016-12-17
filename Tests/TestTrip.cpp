#include "../src/Driver.h"
#include "gtest/gtest.h"

#define RIDE_ID 5
#define START_X 1
#define START_Y 2
#define END_X 3
#define END_Y 4
#define TARIFF 4.3
#define PASSENGERS 3


class TestTrip : public ::testing::Test {
protected:
    Trip *trip;
    int rideId;
    Point start;
    Point end;
    double tariff;
    int passengers;

    virtual void SetUp() {
        this->rideId = RIDE_ID;
        this->start = Point(START_X, START_Y);
        this->end = Point(END_X, END_Y);
        this->tariff = TARIFF;
        this->passengers = PASSENGERS;
        this->trip = new Trip(rideId, start, end, passengers, tariff);
    }

    virtual void TearDown() {
        delete trip;
    }

public:
    TestTrip() {
    }

    ~TestTrip() {

    }
};

/**
 * Check if a cab was added
 */
TEST_F(TestTrip, CheckAddCab) {
    this->trip->move();
    // meters greater than 0:
    EXPECT_GT(this->trip->getMeterPassed(), 0);
}

/**
 * Check if a passenger was added
 */
TEST_F(TestTrip, CheckAddPassenger) {
    this->trip->addPassenger();
    EXPECT_GT(this->trip->getArrPassengers().size(), 0);
    EXPECT_GT(this->trip->getNumPassengers(), 0);
}

/**
 * Check the constructor of trip
 */
TEST_F(TestTrip, CheckConstructor) {
    EXPECT_EQ(this->trip->getRideId(), this->rideId);
    EXPECT_EQ(this->trip->getCurrentPlace().getX(), this->start.getX());
    EXPECT_EQ(this->trip->getCurrentPlace().getY(), this->start.getY());
    EXPECT_EQ(this->trip->getEnd().getX(), this->end.getX());
    EXPECT_EQ(this->trip->getEnd().getY(), this->end.getY());
    EXPECT_EQ(this->trip->getTariff(), this->tariff);
}
