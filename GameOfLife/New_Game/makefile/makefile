CFLAG=-c -Wall -g -pedantic 
CC=gcc
INCS=-I../Berrier_API -I../Game -I../Gameboard -I../Rules -I../SafeGenericHash -I../GenericDLinkedList -I../GeneticListIter  -I../Play -I../Printer -I../MutexManager -I../Init -I../PrintToPPM
LINK=-Wall -g -pedantic -pthread 
OFILES= Game_of_life.o ADT_Berrier.o PrintToPPM.o Printer.o InitBoard.o GameBoard.o PlayGame_UserInterface.o GenericHash.o Manager.o LinkedListGeneric.o LinkedListGenericIter.o PLAY_THE_GAME.o 
SHAREDOBJ=../Rules/libRules.so
LDL=-ldl

all: GameOfLife

GameOfLife: $(OFILES) 
	$(CC) $(LINK) -o natali $(OFILES) $(LDL)

GenericHash.o: ../SafeGenericHash/GenericHash.c ../SafeGenericHash/HashMap.h ../SafeGenericHash/innar.h ../GeneticListIter/list_itr.h ../SafeGenericHash/list.h ../MutexManager/Manager.h
	$(CC) $(CFLAG) $(INCS) ../SafeGenericHash/GenericHash.c  

Manager.o: ../MutexManager/Manager.c ../MutexManager/Manager.h
	$(CC) $(CFLAG) $(INCS) ../MutexManager/Manager.c
	
LinkedListGeneric.o: ../GenericDLinkedList/LinkedListGeneric.c  ../GenericDLinkedList/list.h  ../GenericDLinkedList/innar.h 
	$(CC) $(CFLAG) $(INCS) ../GenericDLinkedList/LinkedListGeneric.c
	
LinkedListGenericIter.o: ../GeneticListIter/LinkedListGenericIter.c ../GeneticListIter/list_itr.h ../GenericDLinkedList/list.h ../GeneticListIter/innar.h
	$(CC) $(CFLAG) $(INCS) ../GeneticListIter/LinkedListGenericIter.c 

PrintToPPM.o: ../PrintToPPM/PrintToPPM.c ../PrintToPPM/PrintToPPM.h ../Gameboard/GameBoard.h 
	$(CC) $(CFLAG) $(INCS) ../PrintToPPM/PrintToPPM.c 

InitBoard.o: ../Init/InitBoard.c ../Init/InitBoard.h ../Gameboard/GameBoard.h
	$(CC) $(CFLAG) $(INCS) ../Init/InitBoard.c 

GameBoard.o: ../Gameboard/GameBoard.c ../Gameboard/GameBoard.h
	$(CC) $(CFLAG) $(INCS) ../Gameboard/GameBoard.c

PlayGame_UserInterface.o: ../Play/PlayGame_UserInterface.c ../Play/PlayGame_UserInterface.h ../Game/Game_of_life.h
	$(CC) $(CFLAG) $(INCS) ../Play/PlayGame_UserInterface.c 
	
Game_of_life.o: ../Game/Game_of_life.c ../Game/Game_of_life.h ../Berrier_API/ADT_Berrier.h ../Gameboard/GameBoard.h
	$(CC) $(CFLAG) $(INCS) ../Game/Game_of_life.c

ADT_Berrier.o: ../Berrier_API/ADT_Berrier.c  ../Berrier_API/ADT_Berrier.h 
	$(CC) $(CFLAG) $(INCS) ../Berrier_API/ADT_Berrier.c ../Berrier_API/ADT_Berrier.h 

Printer.o:../Printer/Printer.c ../Printer/Printer.h ../Gameboard/GameBoard.h 
		$(CC) $(CFLAG) $(INCS) ../Printer/Printer.c
		
PLAY_THE_GAME.o: ../PLAY_THE_GAME.c ../Game/Game_of_life.c  ../Game/Game_of_life.h 
	$(CC) $(CFLAG) $(INCS)  ../PLAY_THE_GAME.c

moviemaker:
	convert *.ppm frame%d.jpg
	ffmpeg -framerate 12 -i frame%d.jpg MyFile.mp4	

makejpg:
	convert *.ppm frame%d.jpg
	
makemovie:
		ffmpeg -framerate 10 -i frame%d.jpg MyFile.mp4
clean:
	rm *.o prog

ppmclean:
	rm *.ppm

jpgclean:
	rm *.jpg

