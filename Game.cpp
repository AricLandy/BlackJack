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
        std::cout << "You have $" << player.get_money() << "\n";
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
        
        
        // If dealer has Ace showing --> offer insurance
        if (dealer.showing_ace()){
            offer_insurance();
        }
        
        // Check if possible for human to split and ask them
        bool human_split_hand = player.split_players_hand();
        
        // Human gets cards
        bool human_no_bust = player.get_cards(deck, false);
        
        // If human busts --> round is over
        if (!human_no_bust){
            std::cout << "\nYou bust --> Dealer wins\n";
            player.remove_money(BET, false);
        }
        
        // Human does not bust
        else {
            // Reveal dealer cards
            std::cout << "\nRevealing Dealer's cards...\n";
            dealer.hand.print_hand(false);
            std::cout << "\n";
            
            // Dealer gets cards
            bool dealer_no_bust = dealer.get_cards(deck);
            
            if (!dealer_no_bust){
                std::cout << "\nDealer busts\n";
                std::cout << player.name << " wins\n";
                player.add_money(BET, false);
            }
            else {
                // Neither player busts
                better_hand better;
                winner winner = better(&player, &dealer);
            
                // Player wins
                if (winner == winner::player1){
                    std::cout << player.name << " wins\n";
                    player.add_money(BET, false);
                }
                // Dealer wins
                else if (winner == winner::player2){
                    std::cout << "Dealer wins\n";
                    player.remove_money(BET, false);
                }
                // Tie
                else {
                    std::cout << "Both players have " << dealer.hand.get_hand_val() <<
                    ": Push\n";
                }
            }
        }
        
    } while (!cash_out(player, dealer));
    
    
    std::cout << "\n\nFinal money: $" << player.get_money() << "\n";
}



winner better_hand::operator()(Player * p1, Player * p2){
   
    int p1Val = p1->hand.get_hand_val();
    int p2Val = p2->hand.get_hand_val();
    
    // This comparator should not be called if hands are above 21 (Although if it is this is a safety)
    // Both bust
    if (p1Val > 21 && p2Val > 21){
        return winner::tie;
    }
    
    // P1 buts
    if (p1Val > 21){
        return winner::player2;
    }
    // P2 busts
    if (p2Val > 21){
        return winner::player1;
    }
    
    // if past this point both are valid
    // so return better hand
    
    if (p1Val > p2Val){
        return winner::player1;
    }
    else if (p2Val > p1Val){
        return winner::player2;
    }
    else { // Same hand value
        // check for blackjack
        bool p1BJ = p1->hand.black_jack();
        bool p2BJ = p2->hand.black_jack();
            
        if (p1BJ && p2BJ){
            return winner::tie;
        }
        if (p1BJ) { std::cout << "SLAT"; return winner::player1; }
        if (p2BJ) { return winner::player2; }
        
        // No busts, same hand val, no blackjacks --> tie
        return winner::tie;
    }
}
