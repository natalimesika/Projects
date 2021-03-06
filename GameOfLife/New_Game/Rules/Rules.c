#include "Rules.h"

#include <stdio.h>

static int Sum_TheNeighbors( GameBoard* boardGame, int _r, int _c,IsAliveprot _isalivfunc);

/*************************/
/*Destiny_decider	     */
/*************************/
int Destiny_decider( GameBoard* boardGame, size_t _r, size_t _c ,IsAliveprot _isalivfunc)
{

	int neighbors;
	int _fate = _isalivfunc( boardGame, _r, _c);
	
	neighbors = Sum_TheNeighbors( boardGame, _r, _c ,_isalivfunc);
	
	if(1 == _fate)
	{
		if(neighbors <= 1 || neighbors > 3) 
		{	
			return 0 ;
		}
		
		else if(neighbors == 2 || neighbors == 3) 				
		{	
			return 1;		
		}
	}
	
	else if(0 == _fate)
	{
		if(3 == neighbors )
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	return 0;
	
}	

/*********************************************/
/*Destiny_decider_More_chance_To_Live	     */
/*********************************************/
int Destiny_decider_More_chance_To_Live( GameBoard* boardGame, size_t _r, size_t _c ,IsAliveprot _isalivfunc)
{
	int neighbors;
	int _fate = _isalivfunc( boardGame, _r, _c);
	
	neighbors = Sum_TheNeighbors( boardGame, _r, _c ,_isalivfunc);
	
	if(1 == _fate)
	{
		if(neighbors <= 1 || neighbors > 6) 
		{	
			return 0;
		}
		
		else 			
		{	
			return 1;		
		}
	}
	
	else if(0 == _fate)
	{
		if(2 == neighbors )
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	return 0;
}	

int Destiny_decider_Less_chance_To_Live( GameBoard* boardGame, size_t _r, size_t _c,IsAliveprot _isalivfunc )
{
	int neighbors;
	int _fate = _isalivfunc( boardGame, _r, _c);
	
	neighbors = Sum_TheNeighbors( boardGame, _r, _c ,_isalivfunc);
	
	if(1 == _fate)
	{
		if(neighbors <= 1 || neighbors > 2) 
		{	
			return 0;
		}
		
		else 			
		{	
			return 1;		
		}
	}
	
	else if(0 == _fate)
	{
		if(3 == neighbors )
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	return 0;
}	

static int Sum_TheNeighbors(GameBoard* boardGame, int _r, int _c,IsAliveprot _isalivfunc)
{
	int counter = 0;
	counter += _isalivfunc( boardGame, _r + 1, _c );
	counter += _isalivfunc( boardGame, _r - 1, _c );
	counter += _isalivfunc( boardGame, _r, _c + 1 );
	counter += _isalivfunc( boardGame, _r, _c - 1 );
	counter += _isalivfunc( boardGame, _r + 1, _c -1 );
	counter += _isalivfunc( boardGame, _r - 1, _c + 1 );
	counter += _isalivfunc( boardGame, _r - 1, _c - 1 );
	counter += _isalivfunc( boardGame, _r + 1, _c + 1 );
	
	return counter;
}

