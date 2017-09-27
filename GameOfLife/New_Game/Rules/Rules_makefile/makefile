CFLAGS=-c -Wall -g -pedantic -pthread -fPIC 
CC=gcc
INCS=-I../Rules -I../../Gameboard

all: libRules.so

libRules.so: Rules.o
	$(CC) -o  ../libRules.so -shared Rules.o
	
Rules.o: ../Rules.c ../Rules.h ../../Gameboard/GameBoard.h
	$(CC) $(CFLAGS) ../Rules.c $(INCS) 

