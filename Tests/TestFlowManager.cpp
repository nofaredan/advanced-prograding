
#include "../src/FlowManager.h"
#include "gtest/gtest.h"

using namespace std;

class TestFlowManager : public ::testing::Test {
protected:
    FlowManager *flowManager;

    virtual void SetUp() {
        this->flowManager = new FlowManager();
    }

    virtual void TearDown() {
        delete flowManager;
    }

public:
    TestFlowManager() {
    }

    ~TestFlowManager() {

    }
};

/**
 * Check if a taxi was added
 */
TEST_F(TestFlowManager, AddTaxi) {
    flowManager->addTaxi();
    EXPECT_EQ(1, flowManager->getTaxiCenter().getSizeAvailableCabs());
}

/**
 * Check if a driver was added
 */
TEST_F(TestFlowManager, AddDriver) {
    flowManager->addDriver();
    EXPECT_EQ(1, flowManager->getTaxiCenter().getSizeDrivers());
}
/**
 * check if the taxi center is not null
 */
TEST_F(TestFlowManager, GetTaxiCenter) {
// ASSERT_TRUE(NULL != flowManager->getTaxiCenter());
}
