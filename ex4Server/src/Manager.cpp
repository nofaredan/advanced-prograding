#include "Manager.h"

using namespace std;

/**
 *  Manager::calculateBestRoute
 *  @param startPoint - starting Point
 *  @param endPoint - ending point
 * Calculates the best route.
 */
void Manager::calculateBestRoute(Point startPoint, Point endPoint) {

    // a queue of nodes:
    queue<Node *> priority;
    Node *endNode = getEndNode();
    Node *priorityNode;
    priorityNode = getCurrentNode();
    priority.push(priorityNode);
    priorityNode->setLongestRode(0);
    vector<Node *> children;

    // while the queue is not empty:
    while (priority.size() > 0) {
        priorityNode = &(*priority.front());
        priority.pop();

        // if we got to the ending point:
        if (*priorityNode == *endNode) {
            printRode(priorityNode);
        }

        // add neighbors to the queue:
        children = addNeighbors(priorityNode);

        // a for loop to push the children into the queue and set their values
        for (int i = 0; i < children.size(); i++) {
            if (children[i]->getLongestRode() == -1) {
                children[i]->setLongestRode(priorityNode->getLongestRode() + 1);
                children[i]->setPreviousNode(priorityNode);
                priority.push(children[i]);
            }
        }
    }
}
