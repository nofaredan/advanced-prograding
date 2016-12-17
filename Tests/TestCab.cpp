#include "../src/Cab.h"
#include "gtest/gtest.h"


class TestCab : public ::testing::Test {
protected:
    Cab *cab;

    virtual void SetUp() {
        this->cab = new Cab();
    }

    virtual void TearDown() {
        delete cab;
    }

public:
    TestCab() {
    }

    ~TestCab() {

    }
};

/**
 * Check if the cab moved
 */
TEST_F(TestCab, CheckMove) {
    // move the car
    this->cab->move();
    // if the cab km is bigger than 0
    EXPECT_GT(this->cab->getMinKm(), 0);
}
