#ifndef BINARYTREE_H
#define BINARYTREE_H
#include "Node.h"
#include <iostream>
#include <vector>


class BinaryTree
{
    public:
        BinaryTree();
        BinaryTree(std::vector<int> *initialValues);
        void addNode(int value);
        void addMultipleNodes(std::vector<int> *values);
        void removeNode(int value);
        void removeAllNodes();
        bool searchNode(int value);
        Node *getRoot();
        int getNumElements();
        std::string stringInOrder() const;
        void getInOrder(std::vector<int> *sortedValues) const;

        // Override of << operator
        friend std::ostream& operator<< (std::ostream& stream, const BinaryTree& tree)
        {
            stream << tree.stringInOrder();
            return stream;
        }

    private:
        Node *root;
        void insertNode(Node *node, Node *parent);
        void nextNode(Node *currentNode, std::vector<int> *sortedValues) const;
        Node *findNode(int value, Node *currentNode);
        Node *nextSuccessor(Node *currentNode);
        void updateParent(Node *removedNode);
        void updateParent(Node *removedNode, Node *nextSuccessorNode);
        void updateLeftChild(Node *removedNode);
        void updateSuccessor(Node *nextSuccessor, Node *removedNode);
};

#endif // BINARYTREE_H
