#ifndef EX1_NODE_H
#define EX1_NODE_H

#include <iostream>

using namespace std;

class Node {

private:
    int longestRode;
    Node *previous;

public:
    Node();

    void setLongestRode(int newLongestRode);

    virtual bool operator==(const Node &node) = 0;

    int getLongestRode();

    void setPreviousNode(Node *previousNode);

    Node *getPreviousNode();

    friend ostream &operator<<(ostream &os, Node &node);

    virtual ostream &print(ostream &os) = 0;
};

#endif //EX1_NODE_H
