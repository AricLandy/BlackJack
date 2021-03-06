//
//  Game.hpp
//  BlackJack
//
//  Created by Aric Landy on 1/7/19.
//  Copyright © 2019 Aric Landy. All rights reserved.
//
#pragma once

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include "Player.hpp"



class Game{

public:
    // Game ctor
    Game(std::string &player_name, std::string &dealer_name);
    
    // Starts the game by dealing the cards
    void deal_cards();
    
    // plays out one hand of the game
    void play();
    
    
private:
    
    // Deck of cards and the players
    Deck deck;
    Dealer dealer;
    Human player;
    
    
};


// Comparator that returns the value of the better hand
// used when a player has an ace and both possibilities are valid (when the ace is 1 and when it is 11)
enum winner { player1, player2, tie };
struct better_hand {
    winner operator()(Hand * h1, Hand * p2);
};














#endif /* Game_hpp */
