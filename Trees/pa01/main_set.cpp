// This file should implement the game using the std::set container class
// Do not include card_list.h in this file
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <set>
#include "card.h"

using namespace std;

int main(int argv, char** argc){
  if(argv < 3){
    cout << "Please provide 2 file names" << endl;
    return 1;
  }
  
  ifstream cardFile1 (argc[1]);
  ifstream cardFile2 (argc[2]);
  string line;

  if (cardFile1.fail() || cardFile2.fail() ){
    cout << "Could not open file " << argc[2];
    return 1;
  }

  set<Card> cardSetAlice;
  set<Card> cardSetBob;

  //Read each file
  while (getline (cardFile1, line) && (line.length() > 0)){
    istringstream ss(line);
    string suit;
    string rank;

    if(ss >> suit >> rank){
      Card c(suit, rank);
      cardSetAlice.insert(c);
    }
  }
  cardFile1.close();

  while (getline (cardFile2, line) && (line.length() > 0)){
    istringstream ss(line);
    string suit;
    string rank;

    if(ss >> suit >> rank){
      Card c(suit, rank);
      cardSetBob.insert(c);
    }
  }
  cardFile2.close();

  // Game Logic
  bool hasMatch = true;
  while(hasMatch){
    hasMatch = false;
    // Alice's turn
    for(auto it = cardSetAlice.begin(); it != cardSetAlice.end(); ++it){
      Card cardA = it->getCard();
      if(cardSetBob.count(cardA)){
        cardSetAlice.erase(cardA);
        cardSetBob.erase(cardA);
        cout << "Alice picked matching card " << cardA << endl;
        // If match found, continue to Bob
        hasMatch = true;
        break; 
      }
    } 
    for(auto it = cardSetBob.rbegin(); it != cardSetBob.rend(); ++it){    
      Card cardB = it->getCard();     
      if(cardSetAlice.count(cardB)){
        cardSetAlice.erase(cardB);
        cardSetBob.erase(cardB);
        cout << "Bob picked matching card " << cardB << endl;
        // If match found, switch to Alice
        hasMatch = true;
        break;
      }
    }
  }
  
  // Print result  
  cout << " " << endl;
  cout << "Alice's cards:" << endl;
  for(set<Card>::iterator it = cardSetAlice.begin(); it != cardSetAlice.end(); ++it){
    Card cardA = it->getCard();
    cout << cardA << endl;
  }
  cout << " " << endl;


  cout << "Bob's cards:" << endl;
  for(set<Card>::iterator it = cardSetBob.begin(); it != cardSetBob.end(); ++it){
    Card cardB = it->getCard();
    cout << cardB << endl;
  }

  return 0;
}
