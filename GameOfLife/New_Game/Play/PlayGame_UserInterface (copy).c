#include "PlayGame_UserInterface.h"

#include <stdio.h>


static void GUI_Interface()
{
	int i;
	for(i = 0; i < 50; ++i)
	{
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");	
		printf("\t\t\t\t\t\t\t \033[01;3%dm Welcome To Game Of Life \n\n", 1 + ( rand()% 6) );
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");	
		usleep(100000);		
		fflush(stdout);
	}
}

/**********************/
/*CreateGame		  */
/**********************/
GameOfLife* CreateNewGame(size_t _nRows, size_t _ncolumns, size_t _numOfThreads, size_t _numOfGeneration, const char* _filename, size_t _stopIfEqual)
{
	GameOfLife* newGame;
	size_t ruleSelect;
	
	GUI_Interface();
	
	newGame = CreateGame( _nRows, _ncolumns, _numOfThreads, _numOfGeneration, _filename, _stopIfEqual);
	
	printf("For default game press \x1b[33m 0 \x1b[0m\n");
	printf("To select a game where players have more chance to live press \x1b[33m 1 \x1b[0m\n");
	printf("To select a game where players have less chance to live press \x1b[33m 2 \x1b[0m\n");
	scanf( "%u", &ruleSelect  );
	
	Load_Rule( newGame,  ruleSelect );
	
	return newGame;
}

/**********************/
/*Run_game			  */
/**********************/
void RunNewGame(GameOfLife* _newGame)
{
	Run_game(_newGame);
	
	return;
	
}
