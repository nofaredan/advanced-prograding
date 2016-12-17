#include "../src/GridNode.h"
#include "gtest/gtest.h"
#define VALUE_X 1
#define VALUE_Y 2
using namespace std;

class TestGridNode : public ::testing::Test {
protected:
    GridNode* gridNode;
    Point point;

    virtual void SetUp() {
        point = Point(VALUE_X,VALUE_Y);
        this->gridNode = new GridNode(point);
    }

    virtual void TearDown() {
       delete gridNode;
    }

public:
    TestGridNode() {
    }

    ~TestGridNode() {

    }
};

/**
 * Check the point values
 */
TEST_F(TestGridNode, CheckPointValues) {
    EXPECT_EQ(VALUE_X,gridNode->getPoint().getX());
    EXPECT_EQ(VALUE_Y,gridNode->getPoint().getY());
}

/**
 * Check the operator ==
 */
TEST_F(TestGridNode, CheckOperatorEquals) {
    const GridNode* secGridNode = new GridNode(Point(VALUE_X,VALUE_Y));
    EXPECT_TRUE(*(Node*)secGridNode == *(Node*)gridNode);
}

/**
 * Check the operator print
 */
TEST_F(TestGridNode, CheckPrint) {
    ostringstream output;
    gridNode->print(output);
    EXPECT_EQ("(1,2)",output.str());
}
/**
 * Check the setters and getters
 */
TEST_F(TestGridNode, CheckSettersGetters){
    this->gridNode->setLongestRode(2);
    EXPECT_EQ(this->gridNode->getLongestRode(),2);

    GridNode* gridNodeForSet = new GridNode();
    this->gridNode->setPreviousNode(gridNodeForSet);
    EXPECT_TRUE(this->gridNode->getPreviousNode() == gridNodeForSet);
}
