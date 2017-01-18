//
// Created by rotem on 29/11/16.
//

#include "Map.h"
using namespace std;

 /*
 * Map::Map
 * C-TOR
 * @parm sizeX - map x size
 * @parm sizeY - map y size
 * @parm mapObstacles - map obstacles
 * @parm arrGrid - arr grid
 */
Map::Map(int sizeX, int sizeY, vector<Point>* mapObstacles,GridNode ***arrGrid)
        : GridManager(sizeX,sizeY, arrGrid)
{
    obstacles = *mapObstacles;

    // initialize the grid:
    initialize();
}

/*
* Map::setNodeType
* C-TOR
* @parm sizeX - map x size
* @parm sizeY - map y size
* @parm mapObstacles - map obstacles
* @parm arrGrid - arr grid
*/
GridNode* Map::setNodeType(int x, int y) {
    for(int i=0; i<obstacles.size(); i++){
        if(x == obstacles[i].getX() && y == obstacles[i].getY()){
            return (GridNode*)new ObstacleNode(Point(x,y));
        }
    }
    return GridManager::setNodeType(x,y);
}

/*
* Map::isDirValid
* C-TOR
* @parm newRow - grid new row
* @parm newColumn - grid new column
*/
bool Map::isDirValid(int newRow, int newColumn) {
    return (GridManager::isDirValid(newRow, newColumn) &&
            (grid[newRow][newColumn]->getName().compare("ObstacleNode")));
}

/**
* destructor.
**/
Map::~Map() {

}
