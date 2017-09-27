CFLAG=-ansi -Wall -g -pedantic -pthread 
INCES=-I/../ADT_Berrier -I/../mu_test

all: prog

prog: ADT_Berrier.o Test_for_berrier.o
	gcc -o prog -pthread *.o

ADT_Berrier.o: ../ADT_Berrier.c ../ADT_Berrier.h
	gcc $(CFLAG) $(INCES)  ../ADT_Berrier.c

Test_for_berrier.o: ../Test_for_berrier.c ../ADT_Berrier.c ../mu_test.h ../ADT_Berrier.h 
	gcc $(CFLAG) $(INCES)  ../Test_for_berrier.c 
	
	
clean:
	rm *.o prog
