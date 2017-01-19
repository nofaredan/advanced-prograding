#include "Node.h"
using namespace std;

/**
 * a constructor.
 */
Node::Node() {
    reset();
}

/**
 * Set the longest rode.
 * @param newLongestRode
 */
void Node::setLongestRode(int newLongestRode) {
    longestRode = newLongestRode;
}

/**
 *
 * @return the longest rode.
 */
int Node::getLongestRode() {
    return longestRode;
}

/**
* reset the node.
**/
void Node::reset() {
    longestRode = -1;
    previous = NULL;
}


/**
 *
 * @param previousNode = the parent of the node.
 */
void Node::setPreviousNode(Node *previousNode) {
    previous = previousNode;
}

/**
 * get the parent node.
 */
Node *Node::getPreviousNode() {
    return previous;
}

/**
 * operator print.
 * @param os = the ostream.
 * @param node = the node
 * @return ostream
 */
ostream &operator<<(ostream &os, Node &node) {
    return node.print(os);
}