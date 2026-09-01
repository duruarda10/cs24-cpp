#include "intbst.h"
#include <iostream>
using namespace std;

int main() {
    IntBST bst;

    bst.insert(64);
    bst.insert(8);
    bst.insert(4);
    bst.insert(32);
    bst.insert(16);
    bst.insert(128);
    bst.insert(512);
    bst.insert(256);

    cout << "In-order: ";
    bst.printInOrder();

    cout << "Pre-order: ";
    bst.printPreOrder();

    cout << "Post-order: ";
    bst.printPostOrder();

    cout << "Sum: " << bst.sum() << endl;
    cout << "Count: " << bst.count() << endl;

    cout << "Contains 64? " << bst.contains(64) << endl;
    cout << "Contains 17? " << bst.contains(17) << endl;

    cout << "Predecessor of 64: " << bst.getPredecessor(64) << endl;
    cout << "Successor of 64: " << bst.getSuccessor(64) << endl;

    bst.remove(64);
    cout << "After removing 64, in-order: ";
    bst.printInOrder();

    return 0;
}
