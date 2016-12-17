#ifndef EX1_MANAGER_H
#define EX1_MANAGER_H

#include "Point.h"
#include "Node.h"
#include <iostream>
#include <queue>
#include <vector>

using std::queue;
using namespace std;

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

    virtual vector<Node *> addNeighbors(Node *node) =0;

    virtual void calculateBestRoute(Point startPoint, Point endPoint);
};

#endif //EX1_MANAGER_H
