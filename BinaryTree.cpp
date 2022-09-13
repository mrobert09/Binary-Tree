#include "Node.h"
#include "BinaryTree.h"
#include <vector>
#include <string>

using std::vector;
using std::string;


BinaryTree::BinaryTree()
// Base constructor
{
    root = nullptr;
}

BinaryTree::BinaryTree(vector<int> *initialValues)
// Constructor if tree is fed starting values in a vector
{
    root = nullptr;
    for(int x = 0; x < (*initialValues).size(); x++){
        addNode((*initialValues)[x]);
    }
}

void BinaryTree::addNode(int value)
// Adds new node to the binary tree
{
    Node *newNode = new Node(value);

    if(root == nullptr){
        root = newNode;
    }
    else{
        insertNode(newNode, root);
    }
}

void BinaryTree::addMultipleNodes(vector<int> *values)
{
    for(int x = 0; x < (*values).size(); x++){
        addNode((*values)[x]);
    }
}

void BinaryTree::removeNode(int value)
// Removes first value of a node found in the binary tree.
{
    Node *removedNode;
    Node *nextSuccessorNode;
    if(root == nullptr){
        return;
    }

    removedNode = findNode(value, root);
    // If node exists
    if(removedNode != nullptr){
        // If node removed is root
        if(removedNode == root){
            // If there is no right subtree
            if(root->getRight() == nullptr){
                // If there is no left subtree either (root was only node in tree)
                if(root->getLeft() == nullptr){
                    root = nullptr;
                }
                else{
                    root = root->getLeft();
                }
            }
            else{
                nextSuccessorNode = nextSuccessor(removedNode->getRight());
                updateSuccessor(nextSuccessorNode, root);
                root = nextSuccessorNode;
            }
            delete removedNode;
        }

        // If next in order successor is parent or is the last node in the binary tree (largest value)
        else if(removedNode->getRight() == nullptr){
            updateParent(removedNode);
            updateLeftChild(removedNode);
            delete removedNode;
        }

        // Get next in order successor
        else{
            nextSuccessorNode = nextSuccessor(removedNode->getRight());
            updateParent(removedNode, nextSuccessorNode);
            updateSuccessor(nextSuccessorNode, removedNode);
            delete removedNode;
        }
    }
}

void BinaryTree::removeAllNodes()
// Probably inefficient but effective way to delete all nodes and free memory.
// Continually removes root node until no nodes are left.
{
    while(root != nullptr){
        removeNode(root->getValue());
    }
}

Node *BinaryTree::nextSuccessor(Node *currentNode)
// Returns the address of the next successor of a node
{
    if(currentNode->getLeft() != nullptr){
        return nextSuccessor(currentNode->getLeft());
    }
    return currentNode;
}

void BinaryTree::updateSuccessor(Node *nextSuccessorNode, Node *removedNode)
// Updates all the leftover connections of a successor when moving its position due to a node removal
{
    // Update successor's current parent and child relationship
//    nextSuccessor->getParent()->setLeft(nextSuccessor->getRight());
//    if(nextSuccessor->getRight() != nullptr){
//        nextSuccessor->getRight()->setParent(nextSuccessor->getParent());
//    }
    updateParent(nextSuccessorNode);
    // Move successor to removed node's position
    nextSuccessorNode->setParent(removedNode->getParent());
    nextSuccessorNode->setLeft(removedNode->getLeft());
    nextSuccessorNode->setRight(removedNode->getRight());
    // Update successor's new children's parent if they exist
    if(nextSuccessorNode->getLeft() != nullptr){
        nextSuccessorNode->getLeft()->setParent(nextSuccessorNode);
    }
    if(nextSuccessorNode->getRight() != nullptr){
        nextSuccessorNode->getRight()->setParent(nextSuccessorNode);
    }
}

void BinaryTree::updateParent(Node *removedNode)
// Checks if removed node was the left or right child of parent and replace parent's child with removed node's child
// A lot of annoying unique cases when shifting binary trees around
{
    if(removedNode->getParent()->getLeft() == removedNode){
        if(removedNode->getLeft() == nullptr) {
            removedNode->getParent()->setLeft(removedNode->getRight());
            if(removedNode->getRight() != nullptr){
                removedNode->getRight()->setParent(removedNode->getParent());
            }
        }
        else {
            removedNode->getParent()->setLeft(removedNode->getLeft());
            if(removedNode->getLeft() != nullptr){
                removedNode->getLeft()->setParent(removedNode->getParent());
            }
        }
    }
    else {
        if(removedNode->getLeft() == nullptr && removedNode->getRight() != nullptr){  // special case to catch removing a node that has only a right child that is itself a right child
            removedNode->getParent()->setRight(removedNode->getRight());
            removedNode->getRight()->setParent(removedNode->getParent());
        }
        else{
            removedNode->getParent()->setRight(removedNode->getLeft());
            if(removedNode->getLeft() != nullptr){
                removedNode->getLeft()->setParent(removedNode->getParent());
            }
        }
    }
}

void BinaryTree::updateParent(Node *removedNode, Node *nextSuccessorNode)
// Overloads the updateParent method to include a successor node. This is part of the process of removing
// a node and replacing it with its next in order successor.
{
    // Check if removed node was the left or right child of parent and replace parent's child with removed node's child
    if(removedNode->getParent()->getLeft() == removedNode){
        removedNode->getParent()->setLeft(nextSuccessorNode);
    }
    else {
        removedNode->getParent()->setRight(nextSuccessorNode);
    }
}

void BinaryTree::updateLeftChild(Node *removedNode)
// Updates the left child's parent to be the removed node's parent
{
    if(removedNode->getLeft() != nullptr){
        removedNode->getLeft()->setParent(removedNode->getParent());
    }
}

bool BinaryTree::searchNode(int value)
// Simple search of the binary tree that returns true if value is found, false otherwise.
{
    if(root == nullptr){
        return false;
    }
    else if(findNode(value, root) == nullptr){
        return false;
    }
    return true;
}

Node *BinaryTree::findNode(int value, Node *currentNode)
// Recursive function that finds the first node of matching value. Returns the address of the node,
// or returns nullptr if node is not found in the tree.
{
    if(value == currentNode->getValue()){
        return currentNode;
    }
    else if(currentNode->getLeft() != nullptr && value <= currentNode->getValue()){
        return findNode(value, currentNode->getLeft());
    }
    else if(currentNode->getRight() != nullptr && value > currentNode->getValue()){
        return findNode(value, currentNode->getRight());
    }
    return nullptr;
}

void BinaryTree::insertNode(Node *node, Node *parent)
// Used by addNode() to insert the new node into the correct position.
// Recursively traverses the tree until it finds the correct leaf.
{
    if(node->getValue() <= parent->getValue()){
        if(parent->getLeft() == nullptr){
            parent->setLeft(node);
            node->setParent(parent);
        }
        else{
            insertNode(node, parent->getLeft());
        }
    }
    else{
        if(parent->getRight() == nullptr){
            parent->setRight(node);
            node->setParent(parent);
        }
        else{
            insertNode(node, parent->getRight());
        }
    }
}

string BinaryTree::stringInOrder() const
// Used for << override for printing in order tree to stdout
{
    if(root == nullptr){
        return "[]";
    }

    vector<int> sortedValues;
    getInOrder(&sortedValues);

    string returnString;
    returnString = "[";
    int y = 0;
    for(int x: sortedValues){
        if(y != 0){
            returnString += ", ";
        }
        returnString += std::to_string(x);
        y++;
    }
    returnString += "]";
    return returnString;
}

void BinaryTree::getInOrder(vector<int> *sortedValues) const
// Creates and returns vector of the sorted values using Depth First Search
{
    if(root != nullptr){
        nextNode(root, sortedValues);
    }
}

void BinaryTree::nextNode(Node *currentNode, vector<int> *sortedValues) const
// Recursive helper function that adds nodes to the vector defined in getInOrder() using Depth First Search
{
    if(currentNode->getLeft() != nullptr){
        nextNode(currentNode->getLeft(), sortedValues);
    }
    (*sortedValues).push_back(currentNode->getValue());
    if(currentNode->getRight() != nullptr){
        nextNode(currentNode->getRight(), sortedValues);
    }
}

Node *BinaryTree::getRoot()
// Returns root
{
    return root;
}

int BinaryTree::getNumElements()
// Returns number of elements in tree
{
    vector<int> numElements;
    getInOrder(&numElements);

    return numElements.size();
}
