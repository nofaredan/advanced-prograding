#ifndef EX1_GRIDNODE_H
#define EX1_GRIDNODE_H

#include "Point.h"
#include "Node.h"
#include <string>

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

    virtual std::string getName();

    bool operator==(const Node &node);

    std::ostream &print(std::ostream &os);
};

#endif //EX1_GRIDNODE_H
