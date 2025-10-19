.DEFAULT_GOAL := all

# Compiler name
CPP = g++
CFLAGS = -Wall -g

################
# targets

# Exception

Exception.o: Exception.cpp
			$(CPP) $(CFLAGS) -c Exception.cpp

# BoardEntity

BoardEntity.o: BoardEntity.cpp 
			$(CPP) $(CFLAGS) -c BoardEntity.cpp

# Board

Board.o: BoardEntity.o Board.cpp
			$(CPP) $(CFLAGS) -c Board.cpp

# Player

Player.o: Player.cpp
			$(CPP) $(CFLAGS) -c Player.cpp

# Dice

Dice.o: Dice.cpp
			$(CPP) $(CFLAGS) -c Dice.cpp

# Game

Game.o: Exception.o Board.o Player.o Dice.o Game.cpp
			$(CPP) $(CFLAGS) -c Game.cpp

# Main

Main: Exception.o BoardEntity.o Board.o Player.o Dice.o Game.o main.cpp
			$(CPP) $(CFLAGS) -c main.cpp
			$(CPP) $(CFLAGS) *.o -o Main

# clean

clean:
		rm -f *.o
		rm -f *.out
		rm -f *.a

# all

all: clean Main

