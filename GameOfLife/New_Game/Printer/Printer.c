#include "Printer.h"

#include "GameBoard.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"


#include <unistd.h>
#include <time.h>
#include <stdio.h>


void* PrintCurrent_boardGame( GameBoard* _gameBoard)
{
	int _x = 0, _y = 0;
	int columns = NumOfCol( _gameBoard);
	int rows = NumOfRows( _gameBoard);
	int printPoint;
	printf("\033[2J");
	
	for(_y = 0; _y < columns; ++_y)
	{
		for(_x = 0; _x < rows; ++_x)
		{	
			printPoint = Search_Point(_gameBoard, _x, _y);
			
			if(1 == printPoint)
			{
				
				printf("\033[01;33m");
				printf(" + ");
			}
			
			if(0 == printPoint)
			{
				printf("\033[01;30m");
				printf(" . ");
			}
		}
		printf("\n");
	}

	fflush(stdout);
	printf("\033[2J");
	
	return NULL;
}


