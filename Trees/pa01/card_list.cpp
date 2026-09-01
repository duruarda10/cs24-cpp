// card_list.cpp
// Author: Shawn, Duru
// Implementation of the classes defined in card_list.h

#include "card_list.h"
#include "card.h"
#include <iostream>

using namespace std;

CardList::~CardList(){
    clear(root);
}

void CardList::insert(Card c){
    insert(root, c, nullptr);
}

void CardList::insert(Node*& n, Card c, Node* p){
    if(contains(c)){ 
        return;
    }    
    if(!n){
        n = new Node(c);
        n->parent = p;
        return;
    }
    if (c>n->card){
        insert(n->right, c, n);
    }
    else if(c<n->card){
        insert(n->left, c, n);
    }
    else{
        return;
    }
}

bool CardList::contains(const Card& c) const{
    if(find(root, c)!=nullptr){
        return true;
    }
    return false;
}

Node* CardList::find(Node* n, const Card& c) const{
    if(!n){
        return nullptr;
    }
    if(n->card == c){
        return n;
    }
    if (c < n->card){
        return find(n->left, c);
    }
    return find(n->right, c);
}

Node* CardList::getPredecessor(Node* n) const{
    Node* curr = find(n, n->card);
    if(!curr){
        return nullptr;
    }
    if (curr->left){
        Node* temp = curr->left;
        while(temp->right){
            temp = temp->right;
        }
        return temp;
    }
    Node* parent = curr->parent;
    while(parent && curr==parent->left){
        curr = parent;
        parent = parent->parent;
    }
    return parent;
}

Node* CardList::getSuccessor(Node* n) const{
    Node* curr = find(n, n->card);
    if(!curr){
        return nullptr;
    }
    if (curr->right){
        Node* temp = curr->right;
        while(temp->left){
            temp = temp->left;
        }
        return temp;
    }
    Node* parent = curr->parent;
    while(parent && curr==parent->right){
        curr = parent;
        parent = parent->parent;
    }
    return parent;
}

void CardList::remove(Card c){
    root = remove(root, c);
}

Node* CardList::remove(Node* n, Card c){
    if(n == nullptr) return nullptr;
    if(c < n->card){
        n->left = remove(n->left, c);
        if(n->left) n->left->parent = n;
    } else if(c > n->card){
        n->right = remove(n->right, c);
        if(n->right) n->right->parent = n;
    } else {
        if(n->left == nullptr){
            Node* temp = n->right;
            if(temp) temp->parent = n->parent;
            delete n;
            return temp;
        } else if(n->right == nullptr){
            Node* temp = n->left;
            if(temp) temp->parent = n->parent;
            delete n;
            return temp;
        } else {
            Node* successor = n->right;
            while(successor->left){
                successor = successor->left;
            }
            n->card = successor->card;
            n->right = remove(n->right, successor->card);
            if(n->right) n->right->parent = n;
        }
    }
    return n;
}

void CardList::clear(Node* n){
    if(n == nullptr) return;
    clear(n->left);
    clear(n->right);
    delete n;
}

void CardList::printAllCards(){
    printInOrder(root);
}

void CardList::printInOrder(Node* n) const{
   if(!n){
    return;
   }
   printInOrder(n->left);
   cout << n->card << endl;
   printInOrder(n->right);
}

CardList::iterator CardList::begin(){
    if(root == nullptr) return nullptr;
    Node* curr = root;
    while(curr->left){
        curr = curr->left;
    }
    return iterator(curr, this);
}

CardList::iterator CardList::end(){
    return iterator(nullptr, this);
}

CardList::iterator CardList::rbegin(){
    if(root == nullptr) return nullptr;
    Node* curr = root;
    while(curr->right){
        curr = curr->right;
    }
    return iterator(curr, this);
}

CardList::iterator CardList::rend(){
    return iterator(nullptr, this);
}

int CardList::playGame(CardList& a, CardList& b){
    bool hasMatch = true;
    while(hasMatch){
        hasMatch = false;
        // Alice's turn
        for(auto it = a.begin(); it != a.end(); ++it){
            Card cardA = it->getCard();
            if(b.contains(cardA)){
                a.remove(cardA);
                b.remove(cardA);
                cout << "Alice picked matching card " << cardA << endl;
                // If match found, continue to Bob
                hasMatch = true;
                break; 
            }
        } 
        for(auto it = b.rbegin(); it != b.rend(); --it){    
            Card cardB = it->getCard();     
            if(a.contains(cardB)){
                a.remove(cardB);
                b.remove(cardB);
                cout << "Bob picked matching card " << cardB << endl;
                // If match found, switch to Alice
                hasMatch = true;
                break;
            }
        }
    }

    cout << " " << endl;
    cout << "Alice's cards:" << endl;
    for(auto it = a.begin(); it != a.end(); ++it){
        Card cardA = it->getCard();
        cout << cardA << endl;
    }
    cout << " " << endl;


    cout << "Bob's cards:" << endl;
    for(auto it = b.begin(); it != b.end(); ++it){
        Card cardB = it->getCard();
        cout << cardB << endl;
    }

    return 0;
}