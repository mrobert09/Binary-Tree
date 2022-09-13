#ifndef NODE_H
#define NODE_H


class Node
{
    public:
        Node(int value);
        int getValue();
        setParent(Node *parentPtr);
        setLeft(Node *leftPtr);
        setRight(Node *rightPtr);
        Node *getParent();
        Node *getLeft();
        Node *getRight();

    private:
        int value;
        Node *parent = nullptr;
        Node *left = nullptr;
        Node *right = nullptr;
        Node *self = this;
};

#endif // NODE_H
