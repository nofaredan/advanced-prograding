#include "GridManager.h"
#include <stdexcept>

/**
 * The constructor.
 * @param size_X = the width of the grid
 * @param size_Y =  the height of the grid
 * @param startPoint = the starting point
 * @param endPoint = the ending point
 * @param arrGrid = the grid
 */
GridManager::GridManager(int size_Y, int size_X, GridNode ***arrGrid)
{

    validate(size_X, size_Y);

    sizeX = size_X;
    sizeY = size_Y;
    grid = arrGrid;

    // initialize the grid:
  //  initialize();


}

/**
 * a distructor.
 */
GridManager::~GridManager() {
    for (int row = 0; row < sizeX; row++) {
        for (int column = 0; column < sizeY; column++) {
            delete grid[row][column];
        }
        delete grid[row];
    }
    delete grid;
}

/**
 * validate - input validity check.
 * @param x - size x
 * @param y - size y
 */
void GridManager::validate(int x, int y) {
    // Check for input validity for age, id, exp.
    if ( (x<= 0) ||  (y <= 0) ){
        throw invalid_argument("the size is not valid");
    }
}

/**
 * Initialize the grid.
 */
void GridManager::initialize() {
    // a for loop that goes over the grid and initialized it:
    for (int row = 0; row < sizeX; row++) {
        grid[row] = new GridNode *[sizeY];
        for (int column = 0; column < sizeY; column++) {
            ///// need to call set node type - MAP and not GridManager
            grid[row][column] = setNodeType(column, sizeX - row - 1);
           // grid[row][column] = new GridNode(Point(column, sizeX - row - 1));
        }
    }
}

GridNode* GridManager::setNodeType(int x, int y){
    return new GridNode(Point(x, y));
}
void GridManager::calculateBestRoute(Point startPoint, Point endPoint) {
    start = startPoint;
    end = endPoint;
    currentRow = getPlaceByPoint(start).getX();
    currentColumn = getPlaceByPoint(start).getY();

    Manager::calculateBestRoute(startPoint, endPoint);
}

/**
 *
 * @return the end node by point.
 */
Node *GridManager::getEndNode() {
    Point placePoint = getPlaceByPoint(end);
    return (Node *) (grid[placePoint.getX()][placePoint.getY()]);
}

/**
 *
 * @param point = a point.
 * @return the place of the point by its x and y:
 */
Point GridManager::getPlaceByPoint(Point point) {
    return Point(sizeX - point.getY() - 1, point.getX());
}

/**
 *
 * @return the current node.
 */
Node *GridManager::getCurrentNode() {
    return (Node *) (grid[currentRow][currentColumn]);
}

/**
 *
 * @param node = a node.
 * @return the neighbors.
 */
vector<Node *> GridManager::addNeighbors(Node *node) {
    // a direction matrix to navigate through the grid:
    int directionMatrix[4][2] = {{0,  -1},
                                 {-1, 0},
                                 {0,  1},
                                 {1,  0}};

    currentRow = getPlaceByPoint(((GridNode *&) node)->getPoint()).getX();
    currentColumn = getPlaceByPoint(((GridNode *&) node)->getPoint()).getY();

    vector<Node *> arrNeighbors;
    int newRow, newColumn;
    Node *currentNode;

    // goes over the 4 directions:
    for (int i = 0; i < 4; i++) {
        newRow = currentRow + directionMatrix[i][0];
        newColumn = currentColumn + directionMatrix[i][1];

        // if the direction is valid:
        if (isDirValid(newRow, newColumn)) {
            currentNode = (Node *) grid[newRow][newColumn];
            arrNeighbors.push_back(currentNode);
        }
    }

    // return the neighbors:
    return arrNeighbors;
}


bool GridManager::isDirValid(int newRow, int newColumn){
    return (newRow >= 0 && newRow < sizeX && newColumn >= 0 && newColumn < sizeY);
}

/**
 * Print the rode at the end of the program.
 * @param node = the last node.
 */
void GridManager::printRode(Node *node) {
    vector<Node *> nodes;

    // while the node is not null, get it's parent:
    while (node != NULL) {
        nodes.push_back(node);
        node = node->getPreviousNode();
    }

    // print the rode:
    for (int i = nodes.size() - 1; i >= 0; i--) {
        std::cout << *(nodes[i]) << std::endl;
    }
}
