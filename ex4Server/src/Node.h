#ifndef EX1_NODE_H
#define EX1_NODE_H

#include <iostream>

//using namespace std;

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

    friend std::ostream &operator<<(std::ostream &os, Node &node);

    virtual std::ostream &print(std::ostream &os) = 0;
};

#endif //EX1_NODE_H
