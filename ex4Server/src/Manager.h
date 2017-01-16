#ifndef EX1_MANAGER_H
#define EX1_MANAGER_H

#include "Point.h"
#include "Node.h"
#include <iostream>
#include <queue>
#include <vector>
#include <stack>

using std::queue;

/**
 * Class manager.
 */
class Manager {

protected:
    Point start, end;

public:
    Manager() {};

    virtual void initialize() =0;

    virtual Node *getEndNode() =0;

    virtual Node *getCurrentNode() =0;

    virtual void printRode(Node *node) =0;

    virtual void setAllRodeNodes(Node *lastNode) = 0;

    virtual std::vector<Node *> addNeighbors(Node *node) =0;

    virtual std::stack<Point*> * calculateBestRoute(Point startPoint, Point endPoint);
};

#endif //EX1_MANAGER_H
