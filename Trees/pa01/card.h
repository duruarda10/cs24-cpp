// card.h
// Author: Shawn, Duru
// All class declarations related to defining a single card go here

#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>

class Card {
public:
    // Constructors
    Card();
    Card(std::string suit, std::string rank);

    // Accessors
    std::string getSuit() const;
    std::string getRank() const;
    Card getCard() const;

    // Comparison Operators
    bool operator<(const Card& other) const;
    bool operator>(const Card& other) const;
    bool operator==(const Card& other) const;
    bool operator!=(const Card& other) const;
    
    friend std::ostream& operator<<(std::ostream& os, const Card& other);

private:
    std::string suit;      
    std::string rank; 

    int getSuitValue() const;
    int getRankValue() const;
};

#endif
