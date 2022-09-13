#ifndef UNITTEST_H
#define UNITTEST_H
#include <random>
#include <vector>
#include "BinaryTree.h"


class UnitTest
{
    public:
        UnitTest();
        UnitTest(int trials);
        void trial();

    private:
        int numFails;
        std::vector<int> initialValues;
        std::default_random_engine generator;
        void testLength(BinaryTree *tree, int numElements);
        void testInOrderDFS(BinaryTree *tree);
        void testRemoveNode(BinaryTree *tree);
        void testRemoveNonExistent(BinaryTree *tree);
};

#endif // UNITTEST_H
