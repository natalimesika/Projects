#include "InitBoard.h"

#include <time.h> /*for random*/
#include <string.h>
#include <stdio.h>

#define BUFF_SIZE 1024

/********************/
/*Init Random Num   */
/********************/
void InitRandomNum(GameBoard* _gameBoard)
{
	size_t x;
	size_t y;
	size_t i;
	size_t rows = NumOfRows(_gameBoard);
	size_t columns = NumOfCol(_gameBoard);
	
	srand(  time(NULL) );
	
	for(i = 0; i < columns * rows; ++i)
	{	
		x = rand()%rows;
		y = rand()% columns;
		
		InsertCoordinate(x, y, _gameBoard);
	}
}

/********************/
/*Init Line         */
/********************/
void Init(GameBoard* _gameBoard)
{
	size_t x;
	size_t y;
	size_t i;
	size_t rows = NumOfRows(_gameBoard);
	size_t columns = NumOfCol(_gameBoard);
	
	for(i = 0; i <  rows; ++i)
	{	
		x = columns/2;
		y = i;
	
		InsertCoordinate(x, y, _gameBoard);
	}

}
/********************/
/*Init Random Num   */
/********************/
void Init_Board_from_file(GameBoard* _gameBoard, const char* _fileName )
{
	char buff[BUFF_SIZE] = {0};
	FILE* fp = NULL;
	char* x;
	char* y;
	int _x;
	int _y;
	
	fp = fopen( _fileName , "r" );
	if ( NULL == fp )
	{
		return;
	}		
	
	while( NULL != fgets(buff,BUFF_SIZE, fp ) )
	{
		x = strtok( x, ",");
		y = strtok(NULL, "\n");
	
		_x = atoi( x );
		_y = atoi( y );
		
		InsertCoordinate(_x, _y, _gameBoard);
	}
}


