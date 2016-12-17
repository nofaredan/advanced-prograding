//
// Created by rotem on 29/11/16.
//

#ifndef EX2_MAP_H
#define EX2_MAP_H

#include "Point.h"
#include "GridManager.h"
#include "ObstacleNode.h"
#include "typeinfo"

class Map: public GridManager {
private:
    vector<Point> obstacles;
public:
    Map(){};
    Map(int sizeX, int sizeY, vector<Point>* mapObstacles, GridNode ***arrGrid);
    GridNode* setNodeType(int x, int y);
    bool isDirValid(int newRow, int newColumn);

    };


#endif //EX2_MAP_H
