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
    player.add_one_card(deck);
    dealer.add_one_card(deck);
    
    std::cout << player.name << " cards: \n";
    player.add_one_card(deck);
    
    // We want to hide the card here
    std::cout << dealer.name << " cards: \n";
    dealer.add_one_card(deck, true);
}

// plays out one hand of the game
void Game::play(){
    
    bool cash_out = false;
    
    std::cout << "BlackJack pays 3:2 \n";
    std::cout << "No Surrender \n";
    
    // While player wants to keep playing
    do {
        
        // Display the amount of money the player has
        std::cout << "\nYou have $" << player.get_money() << "\n";
    
        
        std::cout << "[Push enter to deal cards]\n";
        std::cin.get();
        std::cin.get();
        
        deal_cards();
        
        
        // If dealer has Ace showing --> offer insurance
        if (dealer.showing_ace()){
            while (true) {
                std::cout << "Dealer showing ace. Insurance? (y/n) ";
                char decision;
                std::cin >> decision;
                if (decision == 'y'){
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
        
        // Human gets cards
        bool human_no_bust = player.get_cards(deck);
        
        // If human busts --> round is over
        if (!human_no_bust){
            std::cout << "\nYou bust --> Dealer wins\n";
            player.remove_money(BET);
        }
        
        // Human does not bust
        else {
            
            // Reveal dealer cards
            std::cout << "\nRevealing Dealer's cards...\n";
            dealer.print_hand(false);
            std::cout << "\n";
            
            // Dealer gets cards
            bool dealer_no_bust = dealer.get_cards(deck);
            
            if (!dealer_no_bust){
                std::cout << "\nDealer busts\n";
            }
            
            
            int human_hand = player.get_hand_val();
            int dealer_hand = dealer.get_hand_val();
            better_hand better;
            if (player.has_ace()){
                human_hand = better(player.get_hand_val(), player.get_ace_hand_val());
                if (!human_no_bust && human_hand <= 21){
                    human_no_bust = true;
                }
            }
            if (dealer.has_ace()){
                dealer_hand = better(dealer.get_hand_val(), dealer.get_ace_hand_val());
                if (!dealer_no_bust && dealer_hand <= 21){
                    dealer_no_bust = true;
                }
            }
            
            // See who wins
            
            std::cout << "\n";
            // We know at this point that the human did not bust (already taken care of)
            // Dealer busts
            if (!dealer_no_bust){
                std::cout << player.name << " wins\n";
                player.add_money(BET);
            }
            // Neither bust
            else {
                // Player has higher val
                if (human_hand  > dealer_hand){
                    std::cout << player.name << " wins\n";
                    player.add_money(BET);
                }
                // Dealer has higher val
                else if (human_hand  < dealer_hand){
                    std::cout << "Dealer wins\n";
                    player.remove_money(BET);
                }
                // Hands are the same value
                else {
                    std::cout << "Both players have " << dealer.get_hand_val() <<
                    ": Push\n";
                }
            }
        }
            
        
        
        while (true) {
            std::cout << "You have $" << player.get_money() << "\n";
            std::cout << "\nCash Out? (y or n) ";
            char decision;
            std::cin >> decision;
            if (decision == 'y'){
                cash_out = true;
                break;
            }
            else if (decision == 'n'){
                cash_out = false;
                dealer.reset();
                player.reset();
                break;
            }
            else {
                std::cout << "Please enter y or n\n";
            }
        }
        
    } while (!cash_out);
    
    
    
    std::cout << "\n\nFinal money: $" << player.get_money() << "\n";
    
}




int better_hand::operator()(int val1, int val2){
   
    if (val1 > 21){
        return val2;
    }
    else if (val2 > 21){
        return val1;
    }
    
    // if past this point both are valid
    // so return better hand
    
    else if (val1 > val2){
        return val1;
    }
    else { // val2 >= val1
        return val2;
    }
}
