# Black Jack
An easy to play terminal blackjack simulator

This Project, like the Sudoku solver, was developed before I used Git Hub to show my work, all of the code was written by me, just unfortunately not using proper source control techniques. 
### How to play
1) Compile the code
 ``` shell
 make blackJack
 ```
 2) Start the game
```shell
 ./blackJack
```
 
 
 ## Example
 ```
 Enter your name: Aric
 
 You have $10
 How much do you want to bet: $5
 
 Dealing cards...(push enter to reveal each card)
 
 Aric gets...
  -----------------
 |  Two of Spades  |
  -----------------
 Aric hand value: 2
 
 Dealer gets...
  -------------------
 |  Queen of Hearts  |
  -------------------
 Dealer hand value: 10
 
 Aric gets...
  --------------------
 |  King of Diamonds  |
  --------------------
 Aric hand value: 12
 
 Dealer gets...
 ---Card Hidden---
 
 Do you want another card? (y or n) y
 
 Aric gets...
  ---------------------
 |  Seven of Diamonds  |
  ---------------------
 Aric hand value: 19
 
 Do you want another card? (y or n) n
 
 Dealers hidden card...
  -----------------
 |  Six of Spades  |
  -----------------
 Dealer hand value: 16
 
 Dealer gets...
  -------------------
 |  Queen of Spades  |
  -------------------
 Dealer hand value: 26
 
 Dealer busts
 
 Aric wins
 You have $15
 
 Cash Out? (y or n) y
 
 
 Final money: $15
 Profit: $5
```
