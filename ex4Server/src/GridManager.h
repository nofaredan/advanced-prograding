#ifndef EX1_GRIDMANAGER_H
#define EX1_GRIDMANAGER_H

#include "Manager.h"
#include "GridNode.h"
#include <stack>
#include <mutex>
#include <pthread.h>


/**
 * The Grid manager class.
 */
class GridManager : public Manager {
private:
    int sizeX, sizeY;
public:
    int getSizeX() const;

    int getSizeY() const;

private:
    int currentRow, currentColumn;

    std::stack<Point*> *rodePoints;

    void validate(int x, int y);

public:
    ~GridManager();

    GridManager() {};

    GridManager(int size_X, int size_Y, GridNode ***arrGrid);

    void initialize();

protected:
    GridNode ***grid;
    Node *getEndNode();

    Point getPlaceByPoint(Point point);

    Node *getCurrentNode();

    void printRode(Node *node);

    void setAllRodeNodes(Node *lastNode);

    void resetGrid();

    void deleteRode();

    std::vector<Node *> addNeighbors(Node *node);

    virtual GridNode* setNodeType(int x, int y);

    virtual bool isDirValid(int newRow, int newColumn);

public:
    std::stack<Point*> *calculateBestRoute(Point startPoint, Point endPoint);
    //Point* getPointOnRoad();
};

#endif //EX1_GRIDMANAGER_H
