#include "UnitTest.h"
#include "BinaryTree.h"
#include <iostream>
#include <random>
#include <chrono>
#include <algorithm>
#include <vector>

#define MAX_ELEMENTS 100
#define MAX_NUMBER 100

using std::cout;
using std::endl;
using std::sort;
using std::vector;
using std::default_random_engine;



UnitTest::UnitTest()
{
    // Random seed initialization
    generator = default_random_engine(std::chrono::system_clock::now().time_since_epoch().count());
}

UnitTest::UnitTest(int trials)
{
    // Random seed initialization
    generator = default_random_engine(std::chrono::system_clock::now().time_since_epoch().count());
    numFails = 0;
    for(int x = 0; x < trials; x++){
        cout << "Trial Number " << x+1 << endl;
        trial();
    }
    cout << "Number of failed tests: " << numFails << endl;
}

void UnitTest::trial()
{
    int numElements = generator() % MAX_ELEMENTS;
    cout << "Tree created with " << numElements;
    if(numElements != 1){  // formatting for single element grammar
        cout << " values:" << endl;
        if(numElements == 0){
            cout << endl;
        }
    }
    else {
        cout << " value:" << endl;
    }

    for(int x = 0; x < numElements; x++){
        initialValues.push_back(generator() % MAX_NUMBER);
        cout << initialValues[x] << " ";
    }
    if(numElements > 0){  // formatting purposes
        cout << endl << endl;
    }

    BinaryTree tree(&initialValues);
    sort(initialValues.begin(), initialValues.end());  // sort source array for easier evaluation
    testLength(&tree, numElements);
    testInOrderDFS(&tree);
    testRemoveNode(&tree);
    testRemoveNonExistent(&tree);

    tree.removeAllNodes();  // clears memory after each test
    initialValues.clear();  // destroys vector so it is ready for next test
    cout << "----------------" << endl;
}

void UnitTest::testLength(BinaryTree *tree, int numElements)
{
    if(tree->getNumElements() == numElements){
        cout << "Number of elements: PASSED" << endl;
    }
    else{
        cout << "Number of elements: FAILED" << endl;
        numFails++;
    }
}

void UnitTest::testInOrderDFS(BinaryTree *tree)
{
    bool result = true;
    vector<int> inOrderSearch;
    tree->getInOrder(&inOrderSearch);

    for(int x = 0; x < initialValues.size(); x++){
        if(initialValues[x] != inOrderSearch[x]){
            result = false;
        }
    }

    if(result){
        cout << "In-order search: PASSED" << endl;
    }
    else{
        cout << "In-order search: FAILED" << endl;
        numFails++;
    }
}

void UnitTest::testRemoveNode(BinaryTree *tree)
{
    bool result = true;
    if(initialValues.size() == 0){
        cout << "Remove element: N/A" << endl;
        return;
    }
    int randomIndex = generator() % initialValues.size();
    int valueToRemove = initialValues[randomIndex];
    initialValues.erase(initialValues.begin() + randomIndex);
    tree->removeNode(valueToRemove);
    vector<int> inOrderSearch;
    tree->getInOrder(&inOrderSearch);

    for(int x = 0; x < initialValues.size(); x++){
        if(initialValues[x] != inOrderSearch[x]){
            result = false;
        }
    }

    if(result){
        cout << "Remove element (" << valueToRemove << "): PASSED" << endl;
    }
    else{
        cout << "Remove element (" << valueToRemove << "): FAILED" << endl;
        numFails++;
    }
}

void UnitTest::testRemoveNonExistent(BinaryTree *tree)
{
    bool result = true;
    tree->removeNode(MAX_NUMBER + 1);

    vector<int> inOrderSearch;
    tree->getInOrder(&inOrderSearch);
    for(int x = 0; x < initialValues.size(); x++){
        if(initialValues[x] != inOrderSearch[x]){
            result = false;
        }
    }

    if(result){
        cout << "Remove non-existent element: PASSED" << endl;
    }
    else{
        cout << "Remove non-existent element: FAILED" << endl;
        numFails++;
    }

}
