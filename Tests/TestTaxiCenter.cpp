#include "../src/TaxiCenter.h"
#include "gtest/gtest.h"


class TestTaxiCenter : public ::testing::Test {
protected:
    TaxiCenter *taxiCenter;

    virtual void SetUp() {
        this->taxiCenter = new TaxiCenter();
    }

    virtual void TearDown() {
        delete taxiCenter;
    }

public:
    TestTaxiCenter() {
    }

    ~TestTaxiCenter() {

    }
};

/**
 * Check if the driver and cab were added
 */
TEST_F(TestTaxiCenter, CheckAnswerCall) {
//    this->taxiCenter->answerCall(Trip());
 //   EXPECT_GT(taxiCenter->getSizeDrivers(),0);
 //   EXPECT_GT(taxiCenter->getSizeAvailableCabs(),0);
}
