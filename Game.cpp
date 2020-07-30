//
//  Game.cpp
//  BlackJack
//
//  Created by Aric Landy on 1/7/19.
//  Copyright © 2019 Aric Landy. All rights reserved.
//

#include "Game.hpp"

// Amout of money to bet
int BET = 1;

// Creates the players and the deck
Game::Game(std::string &player_name, std::string &dealer_name) :
    dealer(Dealer(dealer_name)), player(Human(player_name)) {

    // Create the deck
    deck = Deck();
}


// Starts the game by dealing the cards
void Game::deal_cards(){
    player.hand.add_one_card(deck);
    dealer.hand.add_one_card(deck);
    
    std::cout << player.name << " cards: \n";
    player.hand.add_one_card(deck);
    
    // We want to hide the card here
    std::cout << dealer.name << " cards: \n";
    dealer.hand.add_one_card(deck, true);
}


void offer_insurance(){
    while (true) {
        std::cout << "Dealer showing ace. Insurance? (y/n) ";
        char decision;
        std::cin >> decision;
        if (decision == 'y'){
            //--- TODO ---
            std::cout << "Statistically this is a poor decision and therefore this game is not gonna let you do it\n"; // Lol
            break;
        }
        else if (decision == 'n'){
            break;
        }
        else {
            std::cout << "Please enter y or n\n";
        }
    }
}

bool cash_out(Human& player, Dealer& dealer){
    while (true) {
        std::cout << "\nYou have $" << player.get_money() << "\n";
        std::cout << "\nCash Out? (y or n) ";
        char decision;
        std::cin >> decision;
        if (decision == 'y'){
            return true;
        }
        else if (decision == 'n'){
            dealer.reset();
            player.reset();
            return false;
        }
        else {
            std::cout << "Please enter y or n\n";
        }
    }
    return true;
}

bool play_hand(Human& player, Deck& deck, bool playing_split_hand){
    // Human gets cards
    bool human_no_bust = player.get_cards(deck, playing_split_hand);
    
    // If human busts --> round is over
    if (!human_no_bust){
        std::cout << "\nYou bust --> Dealer wins\n";
        player.remove_money(BET, playing_split_hand);
    }
    
    return human_no_bust;
}

bool dealer_get_cards(Dealer& dealer, Deck& deck){
    // Reveal dealer cards
    std::cout << "\nRevealing Dealer's cards...\n";
    dealer.hand.print_hand(false);
    std::cout << "\n";
    
    // Dealer gets cards
    return dealer.get_cards(deck);
}

void decide_winner(Human& player, Dealer& dealer, bool dealer_no_bust,  bool playing_split_hand){

    if (!dealer_no_bust){
        std::cout << "\nDealer busts\n";
        std::cout << player.name << " wins\n";
        player.add_money(BET, playing_split_hand);
    }
    else {
        // Neither player busts
        better_hand better;
        Hand human_hand = playing_split_hand ? player.split_hand : player.hand;
        winner winner = better(&human_hand, &dealer.hand);
        
        // Player wins
        if (winner == winner::player1){
            std::cout << player.name << " wins";
            player.add_money(BET, playing_split_hand);
        }
        // Dealer wins
        else if (winner == winner::player2){
            std::cout << "Dealer wins";
            player.remove_money(BET, playing_split_hand);
        }
        // Tie
        else {
            std::cout << "Both players have " << dealer.hand.get_hand_val() <<
            ": Push";
        }
    }
}

// plays out one hand of the game
void Game::play(){
    
    std::cout << "BlackJack pays 3:2 \n";
    std::cout << "No Surrender \n";
    
    // While player wants to keep playing
    do {
        
        // Display the amount of money the player has
        std::cout << "\nYou have $" << player.get_money() << "\n";
    
        
        std::cout << "[Push enter to deal cards]\n";
        std::cin.get();
        std::cin.get();
        
        // Deal cards to human and dealer
        deal_cards();
        
        
        Card a(Values::Ten, Suits::Spades);
        
        std::vector<Card> temp(2, a);
        std::string s = "testy";
        player.hand = Hand(s, temp);
        player.hand.print_hand();
        
        
        // If dealer has Ace showing --> offer insurance
        if (dealer.showing_ace()){
            offer_insurance();
        }
        
        // Check if possible for human to split and ask them
        bool human_split_hand = player.split_players_hand();
        
        // Play human hand
        if (human_split_hand){
            std::cout << "\n\n--- Playing hand 1 ---\n";
            player.hand.print_hand();
        }
        
        bool player_no_bust = play_hand(player, deck, false);
        bool player_no_bust_split;
        if (human_split_hand){
            std::cout << "\n\n--- Playing hand 2 ---\n";
            player.split_hand.print_hand();
            player_no_bust_split = play_hand(player, deck, true);
        }
        
        // Dealer plays hand
        bool dealer_no_bust;
        if (player_no_bust || (human_split_hand && player_no_bust_split)){
            dealer_no_bust = dealer_get_cards(dealer, deck);
        }
        
        // Decide winner
        if (player_no_bust){
            if (human_split_hand){
                std::cout << "\nHand 1 result: ";
            }
            decide_winner(player, dealer, dealer_no_bust, false);
        }
        // Decide winner for split hand if player split their hand
        if (human_split_hand && player_no_bust_split){
            std::cout << "\nHand 2 result: ";
            decide_winner(player, dealer, dealer_no_bust, true);
        }
        

        
    } while (!cash_out(player, dealer));
    
    
    std::cout << "\n\nFinal money: $" << player.get_money() << "\n";
}



winner better_hand::operator()(Hand * h1, Hand * h2){
   
    int h1Val = h1->get_hand_val();
    int h2Val = h2->get_hand_val();
    
    // This comparator should not be called if hands are above 21 (Although if it is this is a safety)
    // Both bust
    if (h1Val > 21 && h2Val > 21){
        return winner::tie;
    }
    
    // P1 buts
    if (h1Val > 21){
        return winner::player2;
    }
    // P2 busts
    if (h2Val > 21){
        return winner::player1;
    }
    
    // if past this point both are valid
    // so return better hand
    
    if (h1Val > h2Val){
        return winner::player1;
    }
    else if (h2Val > h1Val){
        return winner::player2;
    }
    else { // Same hand value
        // check for blackjack
        bool h1BJ = h1->black_jack();
        bool h2BJ = h2->black_jack();
            
        if (h1BJ && h2BJ){
            return winner::tie;
        }
        if (h1BJ) { return winner::player1; }
        if (h2BJ) { return winner::player2; }
        
        // No busts, same hand val, no blackjacks --> tie
        return winner::tie;
    }
}
