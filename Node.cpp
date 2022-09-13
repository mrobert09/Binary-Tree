#include "Node.h"

Node::Node(int x)
// Constructor. Assigns argument as value of the node. No other parameters are set at node creation.
{
    value = x;
}

int Node::getValue()
// Getter for node value.
{
    return value;
}

Node::setParent(Node *parentPtr)
// Setter for parent.
{
    parent = parentPtr;
}

Node::setLeft(Node *leftPtr)
// Setter for left child.
{
    left = leftPtr;
}

Node::setRight(Node *rightPtr)
// Setter for right child.
{
    right = rightPtr;
}

Node *Node::getParent()
// Getter for parent.
{
    return parent;
}

Node *Node::getLeft()
// Getter for left child.
{
    return left;
}

Node *Node::getRight()
// Getter for right child.
{
    return right;
}
