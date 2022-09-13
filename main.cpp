#include "Node.h"
#include "BinaryTree.h"
#include "UnitTest.h"
#include <iostream>

using std::cout;
using std::endl;
using std::vector;


int main()
{
    // Demo
    BinaryTree tree;
    cout << "Empty tree output: " << tree << endl << endl;  // []

    tree.addNode(4);
    cout << "Root only: " << tree << endl << endl;  // [4]

    tree.removeNode(4);
    cout << "Back to empty (removed 4): " << tree << endl << endl;  // []

    cout << "Adding nodes in the following order: 4, 2, 3, 7, 7, 10, 8, 9" << endl;
    vector<int> newNodes = {4, 2, 3, 7, 6, 10, 8, 9};
    tree.addMultipleNodes(&newNodes);
    cout << "Tree with multiple elements: " << tree << endl << endl;  // [2, 3, 4, 6, 7, 8, 9, 10]

    cout << "Internal structure of tree is:" << endl << endl;
    cout << "   4" << endl;
    cout << " /   \\" << endl;
    cout << "2     7" << endl;
    cout << " \\   / \\" << endl;
    cout << "  3 6   10" << endl;
    cout << "       /" << endl;
    cout << "      8" << endl;
    cout << "       \\" << endl;
    cout << "        9" << endl << endl;

    tree.removeNode(9);
    cout << "Removed bottom right node in tree (9): " << tree << endl << endl;  // [2, 3, 4, 6, 7, 8, 10]

    tree.removeNode(6);
    cout << "Removed leaf in middle of tree (6): " << tree << endl << endl;  // [2, 3, 4, 7, 8, 10]

    tree.removeNode(4);
    cout << "Removed root from the tree (4): " << tree << endl << endl;  // [2, 3, 7, 8, 10]

    tree.removeAllNodes();
    cout << "Removed all nodes from the tree: " << tree << endl << endl;

    // Run Unit Tests
    cout << "#####UNIT TESTS#####" << endl << endl;
    UnitTest test(1000);

}
