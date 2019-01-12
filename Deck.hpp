//
//  Deck.hpp
//  BlackJack
//
//  Created by Aric Landy on 1/6/19.
//  Copyright © 2019 Aric Landy. All rights reserved.
//

#ifndef Deck_hpp
#define Deck_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>

using pair = std::pair<std::string, std::string>;
using vec = std::vector<std::string>;


// Represents the posssible suits for a card
enum Suits { Hearts, Diamonds, Spades, Clubs };

// Represents the possible values for a card
enum Values { Two = 2, Three = 3, Four = 4, Five = 5, Six = 6, Seven = 7, Eight = 8, Nine = 9, Ten = 10 , Jack = 22, Queen = 34, King = 46, Ace = 1 };


// Respresents a card in a deck of cards
struct Card {
    // Card ctor
    Card(Values value_in, Suits suit_in);
    
    // Prints the card to output
    void print(std::string start);
    
    // Returns the value of the card
    int get_value();
    
    // Hold the value and suit of the card
    Values value;
    Suits suit;
};



class Deck {
    
public:
    // Deck ctor
    Deck();
    
    // Shuffles the deck
    void shuffle();
    
    // Deals one card
    Card deal();

    
private:
    
    // Holds the cards in the deck
    std::vector<Card> cards;

};


// Helper finctions used for displaying the cards
// not all are currently used in this program
std::string card_val_string(const Card &c);
std::string card_suit_string(const Card &c);
pair card_string(const Card &c);



#endif /* Deck_hpp */
