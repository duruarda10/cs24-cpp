// card.cpp
// Author: Shawn, Duru
// Implementation of the classes defined in card.h

#include "card.h"
#include <iostream>

using namespace std;

Card::Card(){
    suit = "";
    rank = "";
}

Card::Card(string suit, string rank){
    this->suit = suit;
    this->rank = rank;
}

string Card::getSuit() const{
    return suit;
}

string Card::getRank() const{
    return rank;
}

Card Card::getCard() const{
    return *this;
}

bool Card::operator<(const Card& other) const{
    if(suit == other.getSuit()){
        if(getRankValue() < other.getRankValue()){
            return true;
        } else {
            return false;
        }
    }
    if(getSuitValue() < other.getSuitValue()){
        return true;
    } 
    return false;
}
bool Card::operator>(const Card& other) const{
    if(suit == other.getSuit()){
        if(getRankValue() > other.getRankValue()){
            return true;
        } else {
            return false;
        }
    }
    if(getSuitValue() > other.getSuitValue()){
        return true;
    } 
    return false;
}
bool Card::operator==(const Card& other) const{
    if(suit == other.getSuit() && getRankValue() == other.getRankValue()) return true;
    return false;
}
bool Card::operator!=(const Card& other) const{
    if(suit != other.getSuit() || getRankValue() != other.getRankValue()) return true;
    return false;
}
ostream& operator<<(ostream& os, const Card& other) {
    os << other.getSuit() << " " << other.getRank();
    return os;
}

int Card::getSuitValue() const{
    if(suit == "c") return 1;
    if(suit == "d") return 2;
    if(suit == "s") return 3;
    if(suit == "h") return 4;
    return 0;
}

int Card::getRankValue() const{
    if(rank == "a") return 1;
    if(rank == "2") return 2;
    if(rank == "3") return 3;
    if(rank == "4") return 4;
    if(rank == "5") return 5;
    if(rank == "6") return 6;
    if(rank == "7") return 7;
    if(rank == "8") return 8;
    if(rank == "9") return 9;
    if(rank == "10") return 10;
    if(rank == "j") return 11;
    if(rank == "q") return 12;
    if(rank == "k") return 13;
    return 0;
}



