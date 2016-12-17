#ifndef EX1_GRIDNODE_H
#define EX1_GRIDNODE_H

#include "Point.h"
#include "Node.h"

/**
 * Grid node class.
 */
class GridNode : public Node {
private:
    Point point;

public:
    GridNode() {};

    GridNode(Point newPoint) : point(newPoint) {};

    Point getPoint() const;

    bool operator==(const Node &node);

    ostream &print(ostream &os);
};

#endif //EX1_GRIDNODE_H
