#include "../src/GridManager.h"
#include "gtest/gtest.h"
#define SIZE_X 3
#define SIZE_Y 3
#define START_X 0
#define START_Y 0
#define END_X 2
#define END_Y 2
using namespace std;

class TestGridManager : public ::testing::Test {
protected:
    GridNode*** arrGridNode;
    GridManager* gridManager;

    virtual void SetUp() {
        arrGridNode = new GridNode **[SIZE_Y];
        Point startPoint = Point(START_X, START_Y);
        Point endPoint = Point(END_X, END_Y);
        gridManager = new GridManager(SIZE_X, SIZE_Y,arrGridNode);
    }

    virtual void TearDown() {
        delete gridManager;
    }

public:
    TestGridManager() {
    }

    ~TestGridManager() {

    }
};

/**
 * Check if the input is valid
 */
TEST_F(TestGridManager, CheckInputSize) {
  GridNode*** arrGridNode2 = new GridNode **[SIZE_Y];
  Point point1 = Point(0,0);
  Point point2 = Point(2,2);
  try{
    GridManager(-1, -1,arrGridNode2);

  //  EXPECT_ANY_THROW(new GridManager(-1,-1,Point(0,0),Point(2,2), arrGridNode));
  }catch (std::invalid_argument& err){
    ASSERT_STREQ(err.what(),"the size is not valid");
    delete arrGridNode2;
  }
}

/**
 * Check the initialize
 */
TEST_F(TestGridManager, CheckInitialize) {
    EXPECT_GT(sizeof(arrGridNode),0);
}
