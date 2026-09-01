#include <iostream>
#include <cassert>    
#include "card_list.h"
#include "card.h"

using namespace std;

// Forward declarations of test functions
void test_BST_Public_Methods();
void test_Iterator_Methods();
void test_PlayGame_Logic();

int main() {
    cout << "Running BST Public Method Tests..." << endl;
    test_BST_Public_Methods();
    cout << "PASSED" << endl << endl;

    cout << "Running Iterator Tests..." << endl;
    test_Iterator_Methods();
    cout << "PASSED" << endl << endl;

    cout << "Running PlayGame Tests..." << endl;
    test_PlayGame_Logic();
    cout << "PASSED" << endl << endl;

    cout << "ALL TESTS PASSED!" << endl;
    return 0;
}

void test_BST_Public_Methods() {
    CardList list;
    Card c1("h", "3"), c2("s", "k"), c3("c", "a");

    // Case 1: Empty tree
    assert(list.contains(c1) == false);

    // Case 2: Single node
    list.insert(c1);
    assert(list.contains(c1) == true);

    // Case 3: Multiple nodes
    list.insert(c2);
    list.insert(c3);

    // Case 4: Remove leaf
    list.remove(c3); 
    assert(list.contains(c3) == false);

    // Case 5: Remove non-existent
    list.remove(Card("d1", "2")); 
}

void test_Iterator_Methods() {
    CardList list;
    Card c1("c", "2"), c2("c", "5"), c3("c", "a"); // "a" < "2" < "5"

    // Case 1: Empty tree begin == end
    assert(list.begin() == list.end());
    cout << "Case 1 pass" << endl;

    // Case 2: Single node traversal
    list.insert(c1);
    auto it = list.begin();
    assert(it->getRank() == "2");
    ++it;
    assert(it == list.end());
    cout << "Case 2 pass" << endl;

    // Case 3: Multiple nodes Forward 
    list.insert(c3); list.insert(c2); // Order: a, 2, 5
    auto itF = list.begin();
    assert(itF->getRank() == "a"); ++itF;
    assert(itF->getRank() == "2"); ++itF;
    assert(itF->getRank() == "5");
    cout << "Case 3 pass" << endl;

    // Case 4: Multiple nodes Backward 
    auto itB = list.rbegin();
    assert(itB->getRank() == "5"); --itB;
    assert(itB->getRank() == "2"); --itB;
    assert(itB->getRank() == "a");
    cout << "Case 4 pass" << endl;
    
    // Case 5: Comparison
    assert(list.begin() != list.end());
}

void test_PlayGame_Logic() {
    // 1. Both players with common cards
    CardList alice, bob;
    alice.insert(Card("h", "3")); alice.insert(Card("c", "a"));
    bob.insert(Card("h", "3"));   bob.insert(Card("s", "k"));
    
    // Result: Alice should find h 3 and remove it from both.
    alice.playGame(alice, bob);
    assert(!alice.contains(Card("h", "3")));
    assert(!bob.contains(Card("h", "3")));

    // 2. One empty hand 
    CardList empty, full;
    full.insert(Card("d", "q"));
    int matches = empty.playGame(empty, full);
    assert(matches == 0);

    // 3. No common cards 
    CardList a2, b2;
    a2.insert(Card("c", "2"));
    b2.insert(Card("s", "k"));
    a2.playGame(a2, b2);
    assert(a2.contains(Card("c", "2")));
    assert(b2.contains(Card("s", "k")));
}