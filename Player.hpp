//
//  Player.hpp
//  BlackJack
//
//  Created by Aric Landy on 1/6/19.
//  Copyright © 2019 Aric Landy. All rights reserved.
//

#pragma once

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include "Deck.hpp"
#include <vector>

class Hand;
class Player;
class Dealer;
class Human;
class Strategy;

extern unsigned NUM_DECKS;

// Deals one card to a player
void deal_one(Deck& deck, Hand& hand, bool hide_first=false);


// A class that represents a hand
// separate from the player in case of splitting a hand
class Hand {
    
public:
    
    // Hand class constructor
    Hand(std::string& name, std::vector<Card> cards_in);
    
    // Adds one card to the players hand no matter what
    // used for dealing out initial cards
    void add_one_card(Deck &d, bool hide_first=false);
    
    // Returns the hand_val of the player
    int get_hand_val();
    
    // Returns the value of the ace_hand_val
    int get_ace_hand_val();
    
    // Prints the players hand (must be overwritten)
    void print_hand(bool hide_first=false);
    
    // Returns true if the player has an ace
    bool has_ace();
    
    // Prints the value of the hand (or two values if ace)
    void print_hand_val();
    
    // Returns the number of cards the player has
    int black_jack();
    
    // Returns true if the hand has a soft total
    bool soft_total();
    
    // Vector for the cards in the hand
    std::vector<Card> cards;
    
    // Holds the current value of the players hand
    // if the palyer has an ace, both elements of the pair are used
    int hand_val = 0;
    
    // Bool for if the player has an ace in their hand
    bool ace = false;
    
    // value of a hand with an ace counting the ace as 11
    // 'hand_val' uses the 1 case
    int ace_hand_val = 0;
    
    std::string player_name;
};


// A class that represents a player
class Player {
    
public:
    
    Player(std::string &name_in);
    
    // Holds the players hand
    Hand hand;
    
    // Resets the player for the next hand
    void reset();
    
    // Holds the players name
    std::string name;
    
};



class Human : public Player{

public:
    // Human ctor calls player ctor
    Human(std::string &name_in);
    
    // Resets the player for the next hand
    void reset();
        
    // Adds a card to a players hand if they want
    // returns true if the player wants to double down
    bool get_cards(Deck& deck, bool use_split_hand);
    
    // Returns the amount of money the player has
    double get_money();
    
    // Sets the players money
    void add_money(double money_in, bool use_split_hand);
    
    // Sets the players money
    void remove_money(double money_in, bool use_split_hand);
    
    // A human palyer can bet money on a hand
    double money = 0;
    
    // Tracks if the human has doubled down
    bool double_down = false;
    
    // Split the players hand if they can and want to
    bool split_players_hand();
    
    // Tracks if the human split their hand
    bool player_split_hand = false;
    
    // Tracks if the player doubled down on the split hand
    bool split_hand_double_down = false;
    
    // Holds the humans second hand in the case they split their hand
    Hand split_hand;
    
    // Holds the dealer up-card (used for strategy)
    Card* dealer_up_card;
    
    // Sets the dealer upcard
    void set_dealer_upcard(Card* dealer_card);
    
    // Holds the strategy object for the player
    Strategy* strategy;
};




// A class that represents the dealer
class Dealer : public Player {
    
public:
    
    // Dealer ctor calls player ctor
    Dealer(std::string &name_in);
    
    // Adds a card to the dealers hand if the dealer is under 16
    // returns false if dealer busts
    bool get_cards(Deck & d);
    
    // Returns true if the dealer should take another card
    // false if not
    bool take_card();
    
    // Returns true if the dealer is showing an Ace (used for insurance)
    bool showing_ace();
    
    // Returns the dealers upcard
    Card* get_up_card();
    
};



// This class generates basic strategy suggestions for a player
class Strategy {
    
public:
    
    // Prints decision for player based on cards
    void calculate_decision(Hand* player_cards, Card* dealer_card, bool split);
    
    // Called anytime a card is visible to the player
    void card_seen(const Card& card);
    
    // Resets all cards seen
    void reset();
    
    // Returns the current running count
    int get_running_count();
    
    // Returns the current true count
    int get_true_count();
    
    
private:
    
    // Calculates the total value of the hand without one ace
    int calc_non_ace_total(Hand * hand);
    
    // Holds the current running count
    int running_count = 0;
    
    // Holds the total number of cards seen
    int total_cards_seen = 0;
    
};


#endif /* Player_hpp */
