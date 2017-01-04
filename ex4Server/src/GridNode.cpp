#include "GridNode.h"
using namespace std;
/**
 *
 * @return the point of the node.
 */
Point GridNode::getPoint() const {
    return point;
}

std::string GridNode::getName(){
    return "GridNode";
}

/**
 * operator to compare two grid nodes.
 * @param node = a node to compare with
 * @return true or false - the resualt of the comparison
 */
bool GridNode::operator==(const Node &node) {
    return (point.getX() == ((GridNode &) node).getPoint().getX() &&
            point.getY() == ((GridNode &) node).getPoint().getY());
}

/**
 * A print function.
 * @param os = the ostream
 * @return the ostram
 */
ostream &GridNode::print(ostream &os) {
    return os << "(" << point.getX() << "," << point.getY() << ")";
}