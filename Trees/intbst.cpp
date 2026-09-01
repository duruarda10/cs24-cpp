// intbst.cpp
// Implements class IntBST
// DURU ARDA, 27 JANUARY 2026

#include "intbst.h"
#include <iostream>
using std::cout;
static bool isFirst;

IntBST::IntBST() { 
    root = nullptr;
}

IntBST::~IntBST() {
    clear(root);
    root = nullptr;
}

void IntBST::clear(Node *n) {
    if (!n){
	return;
    }  
    clear(n->left);
    clear(n->right);
    delete n;
}

bool IntBST::insert(int value) {
    if (!root){
    	root = new Node(value);
	return true;
    }
    return insert(value, root);
}

bool IntBST::insert(int value, Node *n) {
    if (value==n->info){
    	return false;
    }
    if (value>n->info){
    	if (!n->right){
	    n->right = new Node(value);
	    n->right->parent = n;
	    return true;
	}
	return insert(value,n->right);
    }
    if (value<n->info){
    	if(!n->left){
	    n->left = new Node(value);
	    n->left->parent = n;
	    return true;
	}
	return insert(value,n->left);
    }
}

void IntBST::printPreOrder() const {
    isFirst = true;
    printPreOrder(root);
    if (!isFirst) cout << endl;
}

void IntBST::printPreOrder(Node *n) const {
    if (!n){
    	return;
    }
    cout << n->info << " ";
    printPreOrder(n->left);
    printPreOrder(n->right);
}

void IntBST::printInOrder() const {
    isFirst = true;
    printInOrder(root);
    if (!isFirst) cout << endl;
}

void IntBST::printInOrder(Node *n) const {
    if (!n){
    	return;
    }
    printInOrder(n->left);
    cout << n->info << " ";
    printInOrder(n->right);
}

void IntBST::printPostOrder() const {
    isFirst = true;
    printPostOrder(root);
    if (!isFirst) cout << endl;
}

void IntBST::printPostOrder(Node *n) const {
    if (!n){
    	return;
    }
    printPostOrder(n->left);
    printPostOrder(n->right);
    cout << n->info << " ";
}

int IntBST::sum() const {
    return sum(root);    
}

int IntBST::sum(Node *n) const {
    if (!n){
    	return 0;
    }
    return n->info + sum(n->left) + sum(n->right);
}

int IntBST::count() const {
    return count(root);
}

int IntBST::count(Node *n) const {
    if (!n){
    	return 0;
    }
    return 1 + count(n->left) + count(n->right);
}

IntBST::Node* IntBST::getNodeFor(int value, Node* n) const{
    if (!n){
    	return nullptr;
    }
    if (value==n->info){
    	return n;
    }
    if (value<n->info){
    	return getNodeFor(value,n->left);
    }
    else{
    	return getNodeFor(value,n->right);
    }
}

bool IntBST::contains(int value) const {
    if (!getNodeFor(value,root)){
    	return false;
    }
    return true;
}

IntBST::Node* IntBST::getPredecessorNode(int value) const{
    Node* n = getNodeFor(value,root);
    if (!n){
    	return nullptr;
    }
    if (n->left){
    	Node* r = n->left;
	while(r->right){
	    r = r->right;
	}
	return r;
    }
    Node* curr = n;
    Node* parent = n->parent;
    while(parent && curr == parent->left){
    	curr = parent;
	parent = parent->parent;
    }
    return parent;
}

int IntBST::getPredecessor(int value) const{
    	Node* n = getPredecessorNode(value);
	if (n){
	    return n->info;
	}
	return 0;
}

IntBST::Node* IntBST::getSuccessorNode(int value) const{
    Node* n = getNodeFor(value,root);
    if (!n){
    	return nullptr;
    }
    if (n->right){
    	Node* r = n->right;
	while(r->left){
	    r = r->left;
	}
	return r;
    }
    Node* curr = n;
    Node* parent = n->parent;
    while(parent && curr==parent->right){
    	curr = parent;
	parent = parent->parent;
    }
    return parent;
}

int IntBST::getSuccessor(int value) const{
    Node* n = getSuccessorNode(value);
    if(n){
    	return n->info;
    }
    return 0;
}

bool IntBST::remove(int value) {
    Node* n = getNodeFor(value, root);
    if (!n) return false;
    if (n->left && n->right) {
        Node* r = n->right;
        while (r->left) {
            r = r->left;
        }
        n->info = r->info;   
        n = r;               
    }

    Node* child = n->left ? n->left : n->right;

    if (child) {
        child->parent = n->parent;
    }

    if (!n->parent) {
        root = child;
    }
    else if (n == n->parent->left) {
        n->parent->left = child;
    }
    else {
        n->parent->right = child;
    }

    delete n;
    return true;
}

