#include "../src/DriverLocationListener.h"
#include "gtest/gtest.h"


class TestStatistics : public ::testing::Test {
protected:
    DriverLocationListener *driverLocationListener;

    virtual void SetUp() {
        this->driverLocationListener = new DriverLocationListener();
    }

    virtual void TearDown() {
        delete driverLocationListener;
    }

public:
    TestStatistics() {
    }

    ~TestStatistics() {

    }
};

/**
 * Check if the question was answered
 */
TEST_F(TestStatistics, CheckAnswerQuestion) {
    ASSERT_TRUE(this->driverLocationListener->answerQuestion() != NULL);
}
