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



void Player::add_one_card(Deck &d, bool hide_first){
    deal_one(d, *this, hide_first);
}


// Returns the best hand of the player
// "best" because will return better value of ace in hand
int Player::get_hand_val(){
    if (ace && ace_hand_val < 21 && ace_hand_val > hand_val){
        return ace_hand_val;
    }
    return hand_val;
}


// Returns the value of the ace_hand_val
int Player::get_ace_hand_val(){
    return ace_hand_val;
}


// Helper function that deals one card to a player
void Player::deal_one(Deck &d, Player &p, bool hide_first){
    
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
    

    // Print the cards and the hand value
    // We only want to print the hand when the player has at least two cards
    if (p.player_cards.size() >= 2){
        p.print_hand(hide_first);
        if (!hide_first){
            p.print_hand_val();
        }
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

int Player::black_jack(){
    return player_cards.size() == 2 && hand_val == 21;
}


// Dealer ctor calls player ctor
Dealer::Dealer(std::string &name_in) : Player(name_in) {}


// Adds a card to the dealers hand if the dealer is under 16
// returns false if dealer busts
bool Dealer::get_cards(Deck & d){
    
    // Get card if hand is less than 17
    while (take_card()){
        // Deal one card to the dealer
        std::cout << name << " hits...\n";
        deal_one(d, *this);
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


void Player::print_hand_val(){
    
    std::cout << name << " hand value: " << hand_val;
    // if the player has an ace and two possible values
    if (ace && ace_hand_val <= 21){
        std::cout << " or " << ace_hand_val;
    }
    std::cout << "\n\n";
}


bool Dealer::showing_ace(){
    // TODO: Assert exactly two cards in hand here
    return player_cards[1].value == Values::Ace;
}


// Prints the card to output
void Player::print_hand(bool hide_first){
    
    std::string middle;
    std::string line;
    for(unsigned i = 0; i < player_cards.size(); ++i){
        
        Card card = player_cards[i];
        
        std::string card_description;
        
        // Hide the first card if dealer has two or fewer cards
        if (hide_first && i == 0){
            card_description = "|  *****  | ";
        }
        else{
            card_description = "|  " + card_val_string(card) + " of " + card_suit_string(card) + "  | ";
        }
        
        middle += card_description;
        line += " " + std::string(card_description.size()-3, '-') + "  ";
    }
    
    
    std::cout << line << "\n";
    std::cout << middle << "\n";
    std::cout << line << "\n";
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
    int winnings = money_in + (money_in * double_down);
    if (black_jack()) { winnings *= 1.5; }
    money += winnings;
}


// TODO: lets remove this duplication

// Sets the players money
void Human::remove_money(int money_in){
    money -= money_in + (money_in * double_down);
}


std::string trim(const std::string& str){
    size_t first = str.find_first_not_of(' ');
    if (std::string::npos == first)
    {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}


// Returns true if the player wants to double down
bool Human::get_cards(Deck & d){
    
    // While it is still possible for the human to get cards
    while (hand_val < 21){
        
        // Ask the player if they want a card
        std::string message = "\nDo you want another card? (y or n";
        message += player_cards.size() == 2 ? " or dd): " : "): ";
        std::cout << message;
        std::string choice;
        std::cin >> choice;
        choice = trim(choice);
        
        // If the player wants another card
        if (choice == "y"){
            deal_one(d, *this);
        }
        else if (choice == "n"){
            break;
        }
        else if (choice == "dd"){
            if (player_cards.size() == 2){
                deal_one(d, *this);
                double_down = true;
                break;
            }
            else {
                std::cout << "Can only double down after exectly two cards" << std::endl;
            }
        }
        
        // if bust
        if (hand_val > 21){
            return false;
        }
    }
    
    std::cin.get();
    std::cin.get();
    
    // return true if not bust, false if bust
    return (hand_val <= 21);
}
