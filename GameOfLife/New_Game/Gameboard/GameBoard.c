#include "GameBoard.h"
#include "HashMap.h"
#include "InitBoard.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h> 
#include <time.h>

typedef struct Coordinate Coordinate; 

struct GameBoard
{
	HashMap* m_origane_gameBoard;
	HashMap* m_nextGeneration;
	size_t m_rows;
	size_t m_columns;
};

struct Coordinate
{
	int m_x;
	int m_y;
};


int IsEqualeCoordinate(const void* _firstKey, const void* _secondKey);
static size_t _HashFunction( const void* _key );
static Coordinate* CreateCoordinate(int _x, int _y);

/********************/
/*Create Game Board */
/********************/
GameBoard* CreateGameBoard(size_t _rows, size_t _columns, size_t _numOfThreads, const char* _filename)
{
	GameBoard* gameBoard;
	
	gameBoard = malloc( sizeof( GameBoard ) );
	if(NULL == gameBoard)
	{
		return NULL;
	}
	
	gameBoard->m_origane_gameBoard = HashMap_Create( _rows, _HashFunction, IsEqualeCoordinate, _numOfThreads );							
	if(NULL == 	gameBoard->m_origane_gameBoard)
	{
		free(gameBoard);
		
		return NULL;
	}
	
	gameBoard->m_nextGeneration = HashMap_Create(_rows, _HashFunction, IsEqualeCoordinate , _numOfThreads);
	if(NULL == gameBoard->m_nextGeneration)
	{
		HashMap_Destroy(&(gameBoard->m_nextGeneration), NULL, NULL);		
		free(gameBoard);
		
		return NULL;
	}
	
	gameBoard->m_rows = _rows;																						
	gameBoard->m_columns = _columns;																					
	
	Init( gameBoard );
	
	return gameBoard;
}

/********************/
/*Is alive          */
/********************/
int IsAlive(GameBoard* _currentBoard, size_t _r, size_t _c)
{
	Coordinate* searcheCoordinate;
	void* pVal;
	pVal = malloc(sizeof(void*) );
	
	searcheCoordinate = CreateCoordinate(_r, _c);
	if(NULL == searcheCoordinate)
	{
		return -1;
	}
	if(MAP_SUCCESS == HashMap_Find( (_currentBoard->m_origane_gameBoard ), searcheCoordinate, &pVal ) )		/*Found!!*/
	{
		return 1;
	}
	return 0;
}


/********************/
/*Update Value      */
/********************/
void Update_Value(GameBoard* _currentBoard, size_t _r, size_t _c ,int _statusForNexGan)
{
	Coordinate* newCoordinate;
	void* pVal;
	void* pVal1;
	void* pVal2;
	pVal = malloc(sizeof(void*) );
	
	if( NULL == pVal )
	{
		return;
	}
	newCoordinate = CreateCoordinate( _r, _c);
	if(NULL == newCoordinate)
	{
		return;
	}

	if(_statusForNexGan == 1)
	{
		HashMap_Insert( _currentBoard->m_nextGeneration , newCoordinate ,(void*)'#' );
	}
	
	if(_statusForNexGan == 0) 
	{
		HashMap_Remove(_currentBoard->m_nextGeneration, newCoordinate, &pVal1, &pVal2);
	}
	
	free(pVal);
	
}

/********************/
/*Is EqualeTables   */
/********************/
int IsEqualeTables(GameBoard* _gameBoard)
{
	int rows = _gameBoard->m_rows;
	int columns = _gameBoard->m_columns;
	int x;
	int y;
	void* pVal;
	Coordinate* searcheCoordinate;
	
	for(x = 0; x < columns; ++x)
	{
		for(y = 0; y < rows; ++y)
		{
			searcheCoordinate = CreateCoordinate(x,y);
			
			if( ( HashMap_Find( (_gameBoard->m_origane_gameBoard ), searcheCoordinate, &pVal ) ) !=
				  HashMap_Find( (_gameBoard->m_nextGeneration ), searcheCoordinate, &pVal ) )
			{
				return 0;
			}
		}
	}
	return 1;
}


/********************/
/*Switch Tables     */
/********************/
void SwitchTables(GameBoard* _gameBoard)
{
	HashMap* temp;
	
	temp = 	*(&_gameBoard->m_nextGeneration);
	*(&_gameBoard->m_nextGeneration) = *(&_gameBoard->m_origane_gameBoard);
	*(&_gameBoard->m_origane_gameBoard) = temp;
}


/********************/
/*Search Point      */
/********************/
int Search_Point(GameBoard* _gameBoard, int _x, int _y)
{
	void* pValue;
	int err;
	Coordinate* searcheCoordinate;
	
	searcheCoordinate = CreateCoordinate(_x, _y);	
	if(NULL == searcheCoordinate)
	{
		return -1;
	}
	err = HashMap_Find( _gameBoard->m_origane_gameBoard ,searcheCoordinate, &pValue );
	
	if( MAP_KEY_NOT_FOUND_ERROR == err) 
	{
		return 0;
	}
	
	else if( MAP_SUCCESS == err ) 
	{
		return 1;	
	}
	return -1;
}

/********************/
/*Static      */
/********************/
static size_t _HashFunction(const void* _key)
{
	if (NULL == _key)
	{
		return 0;
	}
	
	Coordinate* coordinate = (void*)_key;

	return ( ( (coordinate->m_x * coordinate->m_y) * (coordinate->m_x * coordinate->m_y + 1) )/ 2 + coordinate->m_x) ;
	
}

static Coordinate* CreateCoordinate(int _x, int _y)
{
	Coordinate* newCoordinate;
	
	if(_x < 0 || _y < 0)
	{
		return NULL;
	}	
	
	newCoordinate =(Coordinate*)malloc( sizeof (Coordinate) * 1 );
	if(NULL == newCoordinate)
	{
		return NULL;
	}
	
	newCoordinate->m_x = _x;
	newCoordinate->m_y = _y;
	
	return newCoordinate;
}


void CoordinateDestroy(void* _key)
{
	Coordinate* newCoordinate = _key;
	
	free(newCoordinate);
	
	return;

}

int IsEqualeCoordinate(const void* _firstKey, const void* _secondKey)
{
	Coordinate* first;
	Coordinate* sec;

	if(NULL == _firstKey || NULL == _secondKey)
	{
		return -1;	
	}
	first = (Coordinate*)_firstKey;
	sec = (Coordinate*)_secondKey;

	if( first->m_x == sec->m_x && first->m_y == sec->m_y )
	{
		return 1;
	}
	
	return 0;

}


void InsertCoordinate(int _x, int _y,  GameBoard* _gameBoard )
{
	Coordinate* newCoordinate;
	
	newCoordinate = CreateCoordinate( _x, _y);
	if(NULL == newCoordinate)
	{
		return;
	}
	
	HashMap_Insert( _gameBoard->m_origane_gameBoard , newCoordinate, (void*)'#' );
}

int NumOfRows( GameBoard* _board )
{
	return _board->m_rows;
}


int NumOfCol( GameBoard* _board )
{
	return _board->m_columns;
}


void DestroyBoard( GameBoard* _board )
{
	HashMap_Destroy( &_board->m_nextGeneration , CoordinateDestroy, NULL);
	HashMap_Destroy( &_board->m_origane_gameBoard , CoordinateDestroy, NULL);
	
	free(_board);
}


