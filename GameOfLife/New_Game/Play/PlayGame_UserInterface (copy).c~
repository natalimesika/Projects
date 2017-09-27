#include "PlayGame_UserInterface.h"

#include <stdio.h>


/**********************/
/*CreateGame		  */
/**********************/
GameOfLife* CreateNewGame(size_t _nRows, size_t _ncolumns, size_t _numOfThreads, size_t _numOfGeneration, const char* _filename, size_t _stopIfEqual)
{
	GameOfLife* newGame;
	size_t ruleSelect;
	
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
