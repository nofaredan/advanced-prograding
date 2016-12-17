//
// Created by rotem on 29/11/16.
//

#include "Map.h"

Map::Map(int sizeX, int sizeY, vector<Point>* mapObstacles,GridNode ***arrGrid)
        : GridManager(sizeX,sizeY, arrGrid)
{
    obstacles = *mapObstacles;

    // initialize the grid:
    initialize();
}

GridNode* Map::setNodeType(int x, int y) {
    for(int i=0; i<obstacles.size(); i++){
        if(x == obstacles[i].getX() && y == obstacles[i].getY()){
            return (GridNode*)new ObstacleNode(Point(x,y));
        }
    }
    return GridManager::setNodeType(x,y);
}

bool Map::isDirValid(int newRow, int newColumn) {
    return (GridManager::isDirValid(newRow, newColumn) &&
            typeid(grid[newRow, newColumn]).name() == "ObstacleNode");
}