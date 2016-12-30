#ifndef EX1_GRIDMANAGER_H
#define EX1_GRIDMANAGER_H

#include "Manager.h"
#include "GridNode.h"

/**
 * The Grid manager class.
 */
class GridManager : public Manager {
private:
    int sizeX, sizeY;
    int currentRow, currentColumn;


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

    std::vector<Node *> addNeighbors(Node *node);

    virtual GridNode* setNodeType(int x, int y);

    virtual bool isDirValid(int newRow, int newColumn);

public:
    void calculateBestRoute(Point startPoint, Point endPoint);
};

#endif //EX1_GRIDMANAGER_H
