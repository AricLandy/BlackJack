//
//  main.cpp
//  BlackJack
//
//  Created by Aric Landy on 1/6/19.
//  Copyright © 2019 Aric Landy. All rights reserved.
//

#include <iostream>
#include "Game.hpp"



// Single player command line blackjack game
int main() {

    // Get the name
    std::cout << "Name: ";
    std::string name;
    std::cin >> name;
    
    std::string d = "Dealer";
    
    // Create the game and start playing
    Game g(name, d);
    g.play();
    
    
    return 0;
}


