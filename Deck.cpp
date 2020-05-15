//
//  Deck.cpp
//  BlackJack
//
//  Created by Aric Landy on 1/6/19.
//  Copyright © 2019 Aric Landy. All rights reserved.
//

#include "Deck.hpp"
#include <random>
#include <algorithm>
#include <iterator>

// Number of decks
unsigned NUM_DECKS = 2;

// Card ctor
// Assigns values to member variables
Card::Card(Values value_in, Suits suit_in)
: value(value_in), suit(suit_in) {}



// Returns the value of the card
int Card::get_value(){
    return value % 12;
}



// Deck ctor
// Adds all cards to the cards vector
Deck::Deck(){
    // Initialize the deck
    reset_deck();
}


void Deck::reset_deck(){
    
    std::vector<Suits> suits = {Suits::Hearts, Suits::Diamonds, Suits::Spades, Suits::Clubs};
    std::vector<Values> values = {Values::Two, Values::Three, Values::Four, Values::Five,
        Values::Six, Values::Seven, Values::Eight, Values::Nine, Values::Ten, Values::Jack,
        Values::Queen, Values::King, Values::Ace};
    
    for (unsigned i = 0; i < NUM_DECKS; ++i){
        for (Suits suit : suits){
            for(Values val : values){
                Card temp(val, suit);
                cards.push_back(temp);
            }
        }
    }
    // Shuffle the cards
    shuffle();
}



// Shuffles the deck using std shuffle and Mersenne Twister
void Deck::shuffle(){
    std::cout << "AAA" << cards.size()  << "\n";
    std::random_device rand;
    std::mt19937 g(rand());
    std::shuffle(cards.begin(), cards.end(), g);
}



// Returns the card at the back of the deck and removes it
Card Deck::deal(){
    
    // If the deck is empty --> reset it
    if (cards.size() == 0){
        std::cout << "\nDeck empty... Shuffling cards...\n";
        reset_deck();
    }
    
    Card temp = cards.back();
    cards.pop_back();
    return temp;
}


// Helper function used for displaying the card in the terminal
pair card_strings(const Card &c){
    return std::make_pair(card_val_string(c), card_suit_string(c));
}


// Helper function used for displaying the card in the terminal
std::string card_suit_string(const Card &c){
    switch (c.suit){
        case(Suits::Hearts) : {
            return "Hearts";
            break;
        }
        case(Suits::Spades) : {
            return "Spades";
            break;
        }
        case(Suits::Diamonds) : {
            return "Diamonds";
            break;
        }
        case(Suits::Clubs) : {
            return "Clubs";
            break;
        }
    }
}



// Helper function to get the value of a card as a string
std::string card_val_string(const Card &c){
    switch (c.value) {
        
        case (Values::Two) : {
            return "Two";
            break;
        }
        case (Values::Three) : {
            return "Three";
            break;
        }
        case (Values::Four) : {
            return "Four";
            break;
        }
        case (Values::Five) : {
            return "Five";
            break;
        }
        case (Values::Six) : {
            return "Six";
            break;
        }
        case (Values::Seven) : {
            return "Seven";
            break;
        }
        case (Values::Eight) : {
            return "Eight";
            break;
        }
        case (Values::Nine) : {
            return "Nine";
            break;
        }
        case (Values::Ten) : {
            return "Ten";
            break;
        }
        case (Values::Jack) : {
            return "Jack";
            break;
        }
        case (Values::Queen) : {
            return "Queen";
            break;
        }
        case (Values::King) : {
            return "King";
            break;
        }
        case (Values::Ace) : {
            return "Ace";
            break;
        }
    }
}
