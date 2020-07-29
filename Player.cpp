//
//  Player.cpp
//  BlackJack
//
//  Created by Aric Landy on 1/6/19.
//  Copyright © 2019 Aric Landy. All rights reserved.
//

#include "Player.hpp"



// Deals one card to a hand
void deal_one(Deck &deck, Hand &hand, bool hide_first){
    
    // Add the next card to Players hand
    hand.cards.push_back(deck.deal());
    
    // increment hand_val
    // mod by 12 to convert to game value int (as set up in deck.hpp)
    Card next_card = hand.cards.back();
    hand.hand_val += (int)(next_card.get_value());
    if (Ace){
        hand.ace_hand_val +=  (int)(next_card.get_value());
    }
    
    // if the player gets an ace
    if (next_card.value == Values::Ace){
        hand.ace = true;
        // Adding 11 but 1 was already added previously
        hand.ace_hand_val = hand.hand_val + 10;
    }
    
    // Get the suit and values
    std::string suit = card_suit_string(hand.cards.back());
    std::string value = card_val_string(hand.cards.back());
    
    
    // Print the cards and the hand value
    // We only want to print the hand when the player has at least two cards
    if (hand.cards.size() >= 2){
        hand.print_hand(hide_first);
        if (!hide_first){
            hand.print_hand_val();
        }
    }
}



/// Hand class

Hand::Hand(std::string& name_in, std::vector<Card> cards_in){
    player_name = name_in;
    cards = cards_in;
    
    hand_val = 0;
    for (auto card : cards_in){
        hand_val += card.get_value();
        
        if (card.value == Values::Ace){
            ace = true;
        }
    }
    if (ace) {
        ace_hand_val = hand_val + 10;
    }
}

void Hand::add_one_card(Deck& deck, bool hide_first){
    deal_one(deck, *this, hide_first);
}


// Returns the best hand of the player
// "best" because will return better value of ace in hand
int Hand::get_hand_val(){
    if (ace && ace_hand_val < 21 && ace_hand_val > hand_val){
        return ace_hand_val;
    }
    return hand_val;
}


// Returns the value of the ace_hand_val
int Hand::get_ace_hand_val(){
    return ace_hand_val;
}



// Returns true if the player has an ace
bool Hand::has_ace(){
    return ace;
}


int Hand::black_jack(){
    return cards.size() == 2 && hand_val == 21;
}


void Hand::print_hand_val(){
    
    std::cout << player_name << " hand value: " << hand_val;
    // if the player has an ace and two possible values
    if (ace && ace_hand_val <= 21){
        std::cout << " or " << ace_hand_val;
    }
    std::cout << "\n\n";
}


// Prints the card to output
void Hand::print_hand(bool hide_first){
    
    std::string middle;
    std::string line;
    for(unsigned i = 0; i < cards.size(); ++i){
        
        Card card = cards[i];
        
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


/// Player class

// Player ctor just sets the hand value initially to zero
Player::Player(std::string &name_in) : hand(name_in, std::vector<Card>()){
    name = name_in;
}

// Resets the palyer for the next hand
void Player::reset(){
    hand = Hand(name, std::vector<Card>());
}



/// Dealer class

// Dealer ctor calls player ctor
Dealer::Dealer(std::string &name_in) : Player(name_in) {}

// Adds a card to the dealers hand if the dealer is under 16
// returns false if dealer busts
bool Dealer::get_cards(Deck & d){
    
    // Get card if hand is less than 17
    while (take_card()){
        // Deal one card to the dealer
        std::cout << name << " hits...\n";
        deal_one(d, hand, false);
    }
    
    // return true if not bust, false if bust
    return (hand.hand_val <= 21);
}


// Returns true if the dealer should take another card
// false if not
bool Dealer::take_card(){
    return hand.get_hand_val() < 17;
}


bool Dealer::showing_ace(){
    // TODO: Assert exactly two cards in hand here
    // TODO: I dont like indexing into hand - maybe switch this to getter
    return hand.cards[1].value == Values::Ace;
}


/// Human Class

// Human ctor calls player ctor
// Human starts with $10
Human::Human(std::string &name_in) :
Player(name_in), split_hand(name_in, std::vector<Card>()) {}

// Resets the palyer for the next hand
void Human::reset(){
    
    hand = Hand(name, std::vector<Card>());
    if (player_split_hand) {
        split_hand = Hand(name, std::vector<Card>());
    }
    
    double_down = false;
    player_split_hand = false;
    split_hand_double_down = false;
}


// Returns the amount of money the player has
double Human::get_money(){
    return money;
}


// Sets the players money
void Human::add_money(double money_in, bool use_split_hand){
    
    Hand curr_hand = use_split_hand ? split_hand : hand;
    bool curr_double_down = use_split_hand ? split_hand_double_down : double_down;
    
    double winnings = money_in + (money_in * curr_double_down);
    
    if (curr_hand.black_jack()) {
        winnings *= 1.5;
    }
    
    money += winnings;
}


// Sets the players money
void Human::remove_money(double money_in, bool use_split_hand){
    
    bool curr_double_down = use_split_hand ? split_hand_double_down : double_down;
    
    money -= money_in + (money_in * curr_double_down);
}

bool can_split(const Hand& hand){
    if (hand.cards.size() != 2){
        return false;
    }
    if (hand.cards[0].value != hand.cards[1].value){
        return false;
    }
    return true;
}

// Returns true if the playes hand is split
bool Human::split_players_hand(){
    
    // Check if it is possible to split hand
    if (!can_split(hand)){
        return false;
    }
    
    // Ask the user if they want to
    while (true) {
        std::cout << "Do you want to split your hand? (y or n): ";
        char decision;
        std::cin >> decision;
        
        if (decision == 'y') { break; }
        else if (decision == 'n') { return false; }
        else { std::cout << "Please enter y or n\n"; }
    }
    
    // if the user wants to split - split their hand and return true
    std::vector<Card> cards(1, hand.cards[0]);
    hand = Hand(name, cards);
    split_hand = Hand(name, cards);
    player_split_hand = true;
    return true;
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
bool Human::get_cards(Deck& deck, bool use_split_hand){
    
    Hand* curr_hand = use_split_hand ? &split_hand : &hand;
    bool* curr_double_down = use_split_hand ? &split_hand_double_down : &double_down;

    // While it is still possible for the human to get cards
    while (curr_hand->get_hand_val() < 21){
        
        // Ask the player if they want a card
        std::string message = "\nDo you want another card? (y or n";
        message += curr_hand->cards.size() == 2 ? " or dd): " : "): ";
        
        std::cout << message;
        std::string choice;
        std::cin >> choice;
        choice = trim(choice);
        
        // If the player wants another card
        if (choice == "y"){
            deal_one(deck, *curr_hand, false);
        }
        else if (choice == "n"){
            break;
        }
        else if (choice == "dd"){
            if (curr_hand->cards.size() == 2){
                deal_one(deck, *curr_hand, false);
                *curr_double_down = true;
                break;
            }
            else {
                std::cout << "Can only double down after exectly two cards" << std::endl;
            }
        }
        
        // if bust
        if (curr_hand->hand_val > 21){
            return false;
        }
    }
    
    // return true if not bust, false if bust
    return (curr_hand->hand_val <= 21);
}
