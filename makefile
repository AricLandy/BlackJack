# BlackJack Makefile
# Written by Aric Landy

# Name of executaable
EXECUTABLE = blackJack
TESTEX = test

# Name of the compiler
CXX = g++

# Compile arguments
CFLAGS = -Wall -Werror -Wextra -pedantic -O3


make blackJack:
	$(CXX) -std=c++11 main.cpp Deck.cpp Game.cpp Player.cpp $(CFLAGS) -o $(EXECUTABLE)

clean:
	rm -f $(binaries) $(objects) *.o $(EXECUTABLE) $(TESTEX)

.PHONY: blackJack clean test
