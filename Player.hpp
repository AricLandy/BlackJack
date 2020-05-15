//
//  Player.hpp
//  BlackJack
//
//  Created by Aric Landy on 1/6/19.
//  Copyright © 2019 Aric Landy. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include "Deck.hpp"
#include <vector>



// A class that represents a player
class Player {
    
public:
    Player(std::string &name_in);
    
    // Adds one card to the players hand no matter what
    // used for dealing out initial cards
    void add_one_card(Deck &d, bool hide_first=false);
    
    // Returns the hand_val of the player
    int get_hand_val();
    
    // Returns the value of the ace_hand_val
    int get_ace_hand_val();
    
    // Deals one card to a player
    void deal_one(Deck &d, Player &p, bool hide_first=false);
    
    // Prints the players hand (must be overwritten)
    void print_hand(bool hide_first=false);
    
    // Returns true if the player has an ace
    bool has_ace();
    
    // Resets the palyer for the next hand
    void reset();
    
    // Prints the value of the hand (or two values if ace)
    void print_hand_val();

    // Vector fo the dealers cards
    std::vector<Card> player_cards;
    
    // Holds the players name
    std::string name;
    
protected:
    
    // Holds the current value of the players hand
    // if the palyer has an ace, both elements of the pair are used
    int hand_val;
    
    // Bool for if the player has an ace in their hand
    bool ace;
    
    // value of a hand with an ace counting the ace as 11
    // 'hand_val' uses the 1 case
    int ace_hand_val;
    
};



class Human : public Player{

public:
    // Human ctor calls player ctor
    Human(std::string &name_in);
        
    // Adds a card to a players hand if they want
    // returns false if player busts
    bool get_cards(Deck &d);
    
    // Returns the amount of money the player has
    int get_money();
    
    // Sets the players money
    void add_money(int money_in);
    
    // Sets the players money
    void remove_money(int money_in);
    
    // A human palyer can bet money on a hand
    int money;
    
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
    
};



// Helper function that deals one card to a player
void deal_one(Deck &d, Player &p);



#endif /* Player_hpp */
