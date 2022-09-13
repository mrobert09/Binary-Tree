# Binary Tree Exercise

This is a basic binary tree exercise written in C++. This project demonstrates use of classes / objects, code encapsulated and abstracted into different files, and unit tests.

## main.cpp

Used to create the necessary BinaryTree object and/or UnitTest object. The "front end" of the program.

## BinaryTree.cpp

All the logic related to the binary tree structure (not node specific). Has an overloaded "<<" operator for custom printing the binary tree in stdout. Includes the following methods:

### BinaryTree()  -Public
  Default constructor, only inititializes an empty root.

### BinaryTree(vector<int> \*initialValues)  -Public
  Overloaded constructor that can take a vector reference of initial integers to populate the binary tree with.
  
### void addNode(int value) / addMultipleNodes(vector<int> \*values)  -Public
  Adds new node to the tree by passing a value, or adds multiple nodes via vector reference.
  
### void removeNode(int value)  -Public
  Removes the first node found in the tree that matches the value. Deletes removed node from memory.
  
### void removeAllNodes()  -Public
  Removes all nodes from the tree starting at the root. Might not be the most efficient but effective way of freeing up memory when clearing the binary tree.

### Node \*nextSuccessor(Node \*currentNode)  -Private
  Helper function for removeNode, finds the next value in order for tree adjustments.
  
### void updateSuccessor(Node \*nextSuccessorNode, Node \*removedNode)  -Private
  Helper function for removeNode, makes a lot of adjustments to the successor node when it moves positions on the tree.
  
### void updateParent(Node \*removedNode) / updateParent(Node \*removedNode, Node*nestSuccessorNode) / updateLeftChild(Node\* removedNode) -Private
  Updates the parent of a specific node to be removed (or relocated). Attaches the moving node's parent to see it's child, and updates the child to have the moving node's parent as its parent. Overall this method was the most challenging to handle as there are a lot of cases that feel unique that need to be handled. May have been a more elegant way / setup for this. Also have some redundant code that needs to be refactored.
  
### bool searchNode(Node \*removedNode)  -Public
  Returns true if value found in tree, false otherwise.
  
### Node \*findNode(int value, Node \*currentNode)  -Private
  Recursive function used to locate a node in a tree. If the tree was perfectly balanced, this would have a run time of O(log(n)). In a completely unbalanced tree, this would be O(n). Returns the address of the node. Used to support both searchNode and removeNode.
  
### void insertNode(Node *node, Node \*parent)  -Private
  Recursive function used to insert a node into position when adding it to the tree, as well as updating the parent / child connections.
  
### string stringInOrder() const  -Private
  Used by the overloaded "<<". Calls getInOrder to get a sorted list of elements in the tree and puts them in a formatted string.
  
### void getInOrder(vector<int> \*sortedValues) const  -Private
  Uses Depth First Search to get an in order list of elements in tree, putting them into the provided vector.
  
### void nextNode(Node \*currentNode, vector<int> \*sortedValues) const  -Private
  Recursive function used to help getInOrder by grabbing each node in order and adding them to the vector. I created this and getInOrder separately as I originally had getInOrder as a public method that created the vector instead of a private method that was passed a vector so as to not require the user to create vectors. Since refactoring some code this was left in by oversight. The two methods can be combined into a single method.
  
### Node \*getRoot()  -Public
  Returns the root. If no root exists, returns nullptr.
  
### int getNumElements()  -Public
  Returns number of elements in the tree by calling getInOrder and then calculating size of the vector.
