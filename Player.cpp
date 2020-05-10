//
//  Player.cpp
//  BlackJack
//
//  Created by Aric Landy on 1/6/19.
//  Copyright © 2019 Aric Landy. All rights reserved.
//

#include "Player.hpp"



// Player ctor just sets the hand value initially to zero
Player::Player(std::string &name_in) : name(name_in), hand_val(0), ace(false), ace_hand_val(0) {}



void Player::add_one_card(Deck &d, bool print){
    deal_one(d, *this, print, "");
}



// Returns the hand_val of the player
int Player::get_hand_val(){
    return hand_val;
}



// Returns the value of the ace_hand_val
int Player::get_ace_hand_val(){
    return ace_hand_val;
}



// Helper function that deals one card to a player
void Player::deal_one(Deck &d, Player &p, bool print, std::string format){
    
    // Add the next card to Players hand
    p.player_cards.push_back(d.deal());
    
    // increment hand_val
    // mod by 12 to convert to game value int (as set up in deck.hpp)
    Card next_card = p.player_cards.back();
    p.hand_val += (int)(next_card.get_value());
    if (ace){
        ace_hand_val +=  (int)(next_card.get_value());
    }
    
    // if the player gets an ace
    if (next_card.value == Values::Ace){
        p.ace = true;
        // Adding 11 but 1 was already added previously
        p.ace_hand_val = p.hand_val + 10;
    }
    
    // Get the suit and values
    std::string suit = card_suit_string(p.player_cards.back());
    std::string value = card_val_string(p.player_cards.back());

    std::cout << "\n";
    std::cout << p.name << " gets...";
    
    
    if (print){
        p.player_cards.back().print(format);
        std::cout << p.name << " hand value: " << p.hand_val;
        
        // if the player has an ace and two possible values
        if (ace && ace_hand_val <= 21){
            std::cout << " or " << p.ace_hand_val << "\n";
        }
        else{
            std::cout << "\n";
        }
    }
    else {
        std::cout << "\n---Card Hidden---\n";
    }
    
}



// Returns true if the player has an ace
bool Player::has_ace(){
    return ace;
}



// Resets the palyer for the next hand
void Player::reset(){
    
    player_cards.clear();
    hand_val = 0;
    ace = false;
    ace_hand_val = 0;
    
}



// Dealer ctor calls player ctor
Dealer::Dealer(std::string &name_in) : Player(name_in) {}



// Adds a card to the dealers hand if the dealer is under 16
// returns false if dealer busts
bool Dealer::get_cards(Deck & d){
    
    // Get card if hand is less than 17
    while (take_card()){
        // Deal one card to the dealer
        deal_one(d, *this, true, "");
    }
    
    // return true if not bust, false if bust
    return (hand_val <= 21);
}



// Returns true if the dealer should take another card
// false if not
bool Dealer::take_card(){
    
    // if the dealer has an ace
    if (ace){
        if (hand_val > 17 && hand_val <= 21){
            return false;
        }
        if (ace_hand_val > 17 && ace_hand_val <= 21){
            return false;
        }
        if (hand_val > 21 && ace_hand_val > 21){
            return false;
        }
        else {
            return true;
        }
        
    }
    
    // No ace
    else{
        return (hand_val < 17);
    }
}



void Dealer::reveal(){
    std::cout << "\nDealers hidden card...\n";
    player_cards.back().print("");
    std::cout << "Dealer hand value: " << hand_val;
    
    // if the player has an ace and two possible values
    if (ace && ace_hand_val <= 21){
        std::cout << " or " << ace_hand_val << "\n";
    }
    else{
        std::cout << "\n";
    }
}



// Human ctor calls player ctor
// HUman starts with $10
Human::Human(std::string &name_in) : Player(name_in), money(0) {}



// Returns the amount of money the player has
int Human::get_money(){
    return money;
}



// Sets the players money
void Human::add_money(int money_in){
    money += money_in;
}



// Sets the players money
void Human::remove_money(int money_in){
    money -= money_in;
}



bool Human::get_cards(Deck & d){
    
    // While it is still possible for the human to get cards
    while (hand_val < 21){
        
        // Ask the player if they want a card
        std::cout << "\nDo you want another card? (y or n) ";
        char choice;
        std::cin >> choice;
        
        //std::cout << "\n";
        
        // If the player wants another card
        if (choice == 'y'){
            deal_one(d, *this, true, "\n");
        }
        else if (choice == 'n'){
            break;
        }
        
        // if bust
        if (hand_val > 21){
            return false;
        }
    }
    
    // return true if not bust, false if bust
    return (hand_val <= 21);
}
