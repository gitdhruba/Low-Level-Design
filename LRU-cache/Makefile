.DEFAULT_GOAL := all

# Compiler name
CPP = g++
CFLAGS = -Wall -g

################
# targets

# Exception
Exception.o: Exception.cpp
			$(CPP) $(CFLAGS) -c Exception.cpp

# ListNode
ListNode.o: ListNode.cpp
		    $(CPP) $(CFLAGS) -c ListNode.cpp

# LinkedList
LinkedList.o: Exception.o ListNode.o LinkedList.cpp
			$(CPP) $(CFLAGS) -c LinkedList.cpp

# LRUCache
LRUCache.o: Exception.o LinkedList.o LRUCache.cpp
			$(CPP) $(CFLAGS) -c LRUCache.cpp

# Main
Main: Exception.o ListNode.o LinkedList.o LRUCache.o
			$(CPP) $(CFLAGS) -c main.cpp
			$(CPP) $(CFLAGS) *.o -o Main

# clean
clean:
		rm -f *.o
		rm -f *.out
		rm -f *.a

# all
all: clean Main