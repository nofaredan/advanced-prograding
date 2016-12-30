//
// Created by rotem on 10/12/16.
//

#ifndef EX2_OBSTACLENODE_H
#define EX2_OBSTACLENODE_H

#include "GridNode.h"

class ObstacleNode : protected GridNode {

public:
    ObstacleNode(Point newPoint) : GridNode(newPoint) {};
};


#endif //EX2_OBSTACLENODE_H
