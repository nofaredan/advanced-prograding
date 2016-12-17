#include "../src/Passenger.h"
#include "gtest/gtest.h"


class TestPassenger : public ::testing::Test {
protected:
    Passenger *passenger;

    virtual void SetUp() {
        this->passenger = new Passenger();
    }

    virtual void TearDown() {
        delete passenger;
    }

public:
    TestPassenger() {
    }

    ~TestPassenger() {

    }
};

/**
 * Check the random score (not 0)
 */
TEST_F(TestPassenger, CheckRandomScore) {
    int score = this->passenger->randomScore();
    // score is not 0:
    EXPECT_GT(score, 0);
}
