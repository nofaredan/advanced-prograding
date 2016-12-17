#include "../src/Driver.h"
#include "gtest/gtest.h"


class TestDriver : public ::testing::Test {
protected:
    Driver *driver;

    virtual void SetUp() {
        this->driver = new Driver();
    }

    virtual void TearDown() {
        delete driver;
    }

public:
    TestDriver() {
    }

    ~TestDriver() {

    }
};

/**
 * Check if the cab was added
 */
TEST_F(TestDriver, CheckAddCab) {
    this->driver->setCab(Cab());
    // cab is not null
    Cab c = this->driver->getCab();
   ASSERT_TRUE((&c) != NULL);
}
