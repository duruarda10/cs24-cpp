// card_list.h
// Author: Shawn, Duru
// All class declarations related to defining a BST that represents a player's hand

#ifndef CARD_LIST_H
#define CARD_LIST_H
#include "card.h"

struct Node {
    Card card;
    Node *left, *right, *parent;
    Node(Card c) : card(c), left(nullptr), right(nullptr), parent(nullptr) {}
};

class CardList {
private:
    Node* root;
    // Helper functions
    void insert(Node*& n, Card c, Node* p);
    Node* find(Node* n, const Card& c) const;
    Node* remove(Node* n, Card c);
    void printInOrder(Node* n) const;

public:
    CardList() : root(nullptr) {}
    ~CardList();

    void insert(Card c);
    bool contains(const Card& c) const;
    void remove(Card c);
    void clear(Node* n);
    void printAllCards();
    Node* getSuccessor(Node* n) const;
    Node* getPredecessor(Node* n) const;

    class iterator {
        public:
            iterator(Node* n = nullptr, CardList* l = nullptr): curr(n), cardList(l) {}

            // Dereference to get card
            Card* operator->(){
                return &(curr->card);
            }

            iterator& operator++(){
                curr = cardList->getSuccessor(curr);
                return *this;
            }

            iterator& operator--(){
                curr = cardList->getPredecessor(curr);
                return *this;
            }

            bool operator==(const iterator& other) const{
                return other.curr == curr;
            }


            bool operator!=(const iterator& other) const{
                return other.curr != curr;
            }

        private:
            Node* curr;
            CardList* cardList;
    };
    
    iterator begin(); 
    iterator end(); 
    iterator rbegin();
    iterator rend();

    int playGame(CardList& a, CardList& b);
};

#endif
