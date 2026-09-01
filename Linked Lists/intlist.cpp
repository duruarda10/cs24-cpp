// intlist.cpp
// Implements class IntList
// DURU ARDA, JAN 14 2026

#include "intlist.h"

#include <iostream>
using std::cout;

// copy constructor
IntList::IntList(const IntList& source) {
    head = nullptr;
    tail = nullptr;
    if (!source.head){
    	return;
    }

    head = new Node;
    head->info = source.head->info;
    head->next = nullptr;
    tail = head;

    for (Node* p = source.head->next; p!=nullptr; p = p->next){
    	Node* n = new Node;
	n->info = p->info;
	n->next = nullptr;

	tail->next = n;
	tail = n;
    }
}

// destructor deletes all nodes
IntList::~IntList() {
    Node* p = head;
    while(p){
    	Node* temp = p;
	p = p->next;
	delete temp;
    }
    head = nullptr;
    tail = nullptr;
}


// return sum of values in list
int IntList::sum() const {
    int total = 0;
    for (Node* p = head; p!=nullptr; p = p->next){
    	total += p->info;
    }
    return total;
}

// returns true if value is in the list; false if not
bool IntList::contains(int value) const {
    for (Node* p = head; p!=nullptr; p = p->next){
    	if (p->info==value){
	    return true;
	}
    }
    return false;
}

// returns maximum value in list, or 0 if empty list
int IntList::max() const {
    if (!head){
    	return 0;
    }
    int max = head->info;
    for (Node* p = head->next; p!=nullptr; p = p->next){
    	if (p->info > max){
	    max = p->info;
	}
    }
    return max;
}

// returns average (arithmetic mean) of all values, or
// 0 if list is empty
double IntList::average() const {
    if (!head){
    	return 0.0;
    }
	int total = 0;
	int counter = 0;
	for (Node* p = head; p!=nullptr; p = p->next){
	    total += p->info;
	    counter ++;
	}
	return static_cast<double>(total)/counter;
}

// inserts value as new node at beginning of list
void IntList::push_front(int value) {
    Node* n = new Node;
    n->info = value;
    n->next = head;
    head = n;

    if (!tail){
    	tail = head;
    }
}

// append value at end of list
void IntList::push_back(int value) {
    Node* n = new Node;
    n->info = value;
    n->next = nullptr;

    if(!head){
    	head = tail = n;
    }
    else{
    	tail->next = n;
	tail = n;
    }
}

// return count of values
int IntList::count() const {
   int counter = 0;
   for (Node* p = head; p!=nullptr; p = p->next){
   	counter++;
   }
   return counter;
}


//Assignment operator should copy the list from the source
//to this list, deleting/replacing any existing nodes
IntList& IntList::operator=(const IntList& source){
    if (this == &source){
    	return *this;
    }

    Node* p = head;
    while(p){
    	Node* temp = p;
	p = p->next;
	delete temp;
    }
    head = nullptr;
    tail = nullptr;

    if (!source.head){
    	return *this;
    }

    head = new Node;
    head->info = source.head->info;
    head->next = nullptr;
    tail = head;

    for (Node* q = source.head->next; q!=nullptr; q = q->next){
    	Node* n = new Node;
	n->info = q->info;
	n->next = nullptr;

	tail->next = n;
	tail = n;
    }
    return *this;
}

// constructor sets up empty list
IntList::IntList(){ 
    head = nullptr;
    tail = nullptr; 
}


// DO NOT CHANGE ANYTHING BELOW (READ IT THOUGH)

// print values enclose in [], separated by spaces
void IntList::print() const {
    Node *n = head;
    cout << '[';
    while (n) {
        cout << n->info;
        if (n->next)
            cout << " ";
        n = n->next;
    }
    cout << ']';
}

