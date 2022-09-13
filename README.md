# Binary Tree Exercise

This is a basic binary tree exercise written in C++. This project demonstrates use of classes / objects, code encapsulated and abstracted into different files, and unit tests.

## main.cpp

Used to create the necessary BinaryTree object and/or UnitTest object. The "front end" of the program.

## BinaryTree.cpp

All the logic related to the binary tree structure (not node specific). Has an overloaded "<<" operator for custom printing the binary tree in stdout which can be found in the header file. This is where the bulk of the logic of the program occurs. Includes the following methods:

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
  
## Node.cpp

Holds the Node class / methods. As the interaction with nodes occurs within the BinaryTree class, this class mostly just has basic data held by the nodes. Each node has 5 main data members:
  - Value
  - Parent Node
    - nullptr if root
  - Left Child
    - nullptr if doens't exist
  - Right Child
    - nullptr if doesn't exist
  -  Address of self in memory
  
In addition, there are getters and setters where appropriate.
  
## UnitTest.cpp
  
Holds the UnitTest class and it's methods. I did not use a library for UnitTests and instead created them on my own. Most common way to call the UnitTest is to pass an integer to the constructor which is the number of tests to run. At the top of the file you can define the max number of elements (MAX_ELEMENTS) to choose and the may number each element can be (MAX_NUMBER). Currently the range is 0 - MAX for both. Each trial creates a new BinaryTree class, passes in a random number of elements of random values based on the MAX_ELEMENTS and MAX_NUMBER values, then deconstructs each tree before starting again. At the end of the tests, prints out how many tests failed. Runs 4 tests:
  
### Length
  Tests that the binary tree has the same number of elements in it that was passed to it. Does so by comparing the size of the vector generated randomly and the size of the binary list returned.
  
### In-Order Depth First Search
  Tests that the elements are being returned in the correct numerical order when performing a depth first search. As a byproduct, it is also testing that elements were inserted correctly as well.
  
### Remove Node
  Tests that removing an element works as expected. Does so by randomly picking an index in the original vector and removing the value located there, and then removing that same value from the binary tree. It then compares the in order depth first search with what is left of the sorted vector to check for equality. Due to the structure of the binary tree, it doesn't matter if the indices of same numbers is correct (for example, if there were three 5s in the vector and it removed the third one, it is okay if the binary tree removes the first one it encounters).
  
### Remove Non-Existent Node
  Tests that removing an element that isn't in the list doesn't break the tree. Currently it does this simply by attempting to remove a value of 1 more than the max element. I recognize though that this isn't a robust test and misses many cases of bad removal (lower than minimum, middle of the tree, invalid characters, etc.)
