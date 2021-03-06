#include "Game_of_life.h"
#define _GNU_SOURCE /* dlsym */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>	/*strcpy*/
#include <pthread.h>
#include <dlfcn.h>
#include <assert.h>
#include <time.h>
#include <unistd.h>


#include "ADT_Berrier.h"
#include "GameBoard.h"
#include "Printer.h"
#include "PrintToPPM.h"

#define BUFF_SIZE (1024)
#define DONT_STOP_IF_EQUAL (0)
#define STOP_IF_EQUAL (1)


typedef int (*IsAliveprota)(GameBoard* _currentBoard, size_t _r, size_t _c);

typedef int (*RulesFunction)(GameBoard* boardGame, size_t _r, size_t _c ,IsAliveprota a);

typedef struct CalcForOne_Thread CalcForOne_Thread; 

struct GameOfLife
{
	GameBoard* boardGame;
	CalcForOne_Thread* m_eachThread;
	size_t m_numOfGen;		
	size_t m_maxGen;	
	int m_nThreads;
	int m_rows;
	int m_columns;
	int m_stopIfequal;
	size_t m_selection;
	 
	void* m_handler_libs;	
	RulesFunction m_ruleFunc;
};

struct CalcForOne_Thread
{
	Barrier* m_barrier;
	GameBoard* m_boardGame_ForLimit;
    GameOfLife* m_game;
	size_t m_maxGen;	
	size_t m_numOfGen;	
	size_t m_startColoumn;
	size_t m_startRow;
	size_t m_endColoumn;
	size_t m_endRow;
};


static void Divide_board( GameOfLife* _gameboard);
static void Run_Threads( GameOfLife* _gameboard);
static void* Update_ParamsPerThread( void* _gameboard);


/**********************/
/*CreateGame		  */
/**********************/
GameOfLife* CreateGame(size_t _rows, size_t _ncolumns, size_t _numOfThreads, size_t _numOfGeneration ,const char* _filename, size_t _stopIfEqual)
{
	GameOfLife* gameOfLife;
	
	if(_rows < 0 || _ncolumns < 0 || _numOfThreads < 0)
	{
		return NULL;
	}
	
	gameOfLife = malloc( sizeof( GameOfLife ) * 1 );
	if(NULL == gameOfLife)
	{
		return NULL;
	}
	/*create new boardGame*/
	gameOfLife->boardGame = CreateGameBoard( _rows, _ncolumns, _numOfThreads, _filename);
	
	/*Creating boundaries for each thread -each thread will update only his boundaries*/
	gameOfLife->m_eachThread = (CalcForOne_Thread*)malloc( sizeof( CalcForOne_Thread ) * _numOfThreads);
	if(NULL == gameOfLife->m_eachThread)
	{
		DestroyBoard( gameOfLife->boardGame );
		free(gameOfLife);
		return NULL;
	}
	
	gameOfLife->m_rows = _rows;
	gameOfLife->m_columns = _ncolumns; 
	gameOfLife->m_nThreads = _numOfThreads;
	gameOfLife->m_numOfGen = 0;
	gameOfLife->m_maxGen = _numOfGeneration;
	
	gameOfLife->m_stopIfequal = _stopIfEqual;
	
	if(_stopIfEqual != DONT_STOP_IF_EQUAL  &&  _stopIfEqual != STOP_IF_EQUAL )
	{
		gameOfLife->m_stopIfequal = DONT_STOP_IF_EQUAL;
	}
	
	
	return gameOfLife;
}

/**********************/
/*Run_game			  */
/**********************/
void Run_game(GameOfLife* _gameOfLife)
{
	if(NULL == _gameOfLife)
	{
		return;
	}
	
	Divide_board( _gameOfLife );
	Run_Threads( _gameOfLife );
	Destroy(_gameOfLife);
	
	return;
}


/**********************/
/*Destroy			  */
/**********************/
void Destroy(GameOfLife* _gameOfLife)
{
	int i;
	if(NULL == _gameOfLife)
	{
		return;
	}
	
	for(i = 0; i < _gameOfLife->m_nThreads; ++i )
	{
		barrier_destroy( _gameOfLife->m_eachThread[i].m_barrier );
	}

	free(_gameOfLife->m_eachThread);
	DestroyBoard(_gameOfLife->boardGame);
	
	free(_gameOfLife);
	
	return;
}


void Load_Rule( GameOfLife* _gameOfLife, size_t _selection )
{
	assert(NULL != _gameOfLife);

	char defaultRules[] = "Destiny_decider";
	char more_chance[] =  "Destiny_decider_More_chance_To_Live";
	char less_chance[] =  "Destiny_decider_Less_chance_To_Live";
	char rule[BUFF_SIZE];

	_gameOfLife->m_handler_libs = dlopen( "../Rules/libRules.so", RTLD_LAZY );
	if(NULL == _gameOfLife->m_handler_libs )
	{
		return;
	}
	
	if(1 == _selection)
	{
		strcpy( rule, more_chance );
	}
	
	if(2 == _selection)
	{
		strcpy( rule, less_chance );
	}

	else
	{
		strcpy( rule, defaultRules );
	}
	
	_gameOfLife->m_ruleFunc = dlsym(_gameOfLife->m_handler_libs, rule );
	if (NULL == _gameOfLife->m_ruleFunc)
	{
		return;
	}
}

/**********************/
/*STATICS FUNCTIONS*/
/**********************/
static void Divide_board(GameOfLife* _gameboard)
{
	int i;
	size_t numOfThreads = 		_gameboard->m_nThreads;
	int endRow =				_gameboard->m_rows;
	int endColumPerThred =  	_gameboard->m_columns / numOfThreads;
	Barrier* barrier;
	
	if(_gameboard->m_stopIfequal == STOP_IF_EQUAL )
	{
		barrier =  BarrierInit( numOfThreads, SwapAndPrint, _gameboard );
	}
	
	else if(_gameboard->m_stopIfequal == DONT_STOP_IF_EQUAL  )
	{
		barrier =  BarrierInit( numOfThreads, SwapAndPrintGeneration, _gameboard );
	}

	for (i = 0; i < numOfThreads; ++i )																	
	{
		( _gameboard->m_eachThread[i] ).m_startColoumn =  i * (endColumPerThred);
		( _gameboard->m_eachThread[i] ).m_endColoumn =  ( endColumPerThred * (i + 1) -1);
		( _gameboard->m_eachThread[i] ).m_startRow  = 0;						
		( _gameboard->m_eachThread[i] ).m_endRow   = endRow - 1;
		( _gameboard->m_eachThread[i] ).m_boardGame_ForLimit = _gameboard->boardGame;
		( _gameboard->m_eachThread[i] ).m_barrier  = barrier;
		( _gameboard->m_eachThread[i] ).m_maxGen   = _gameboard->m_maxGen;
		( _gameboard->m_eachThread[i] ).m_numOfGen = _gameboard->m_numOfGen;
		( _gameboard->m_eachThread[i] ).m_game 	   = _gameboard;
	}
	
	/*If the board is not divisible by the number of thread - the last thread will get the remainder*/
	if( _gameboard->m_columns % numOfThreads != 0)
	{
		( _gameboard->m_eachThread[ numOfThreads-1 ] ).m_endColoumn = (_gameboard->m_columns)-1;
	}
	return;
}

/*create the threads*/
static void Run_Threads(GameOfLife* _gameboard)
{
	int i = 0;
	size_t numOfThreads = _gameboard->m_nThreads;
	pthread_t threads[numOfThreads];
	
	for (i = 0; i < numOfThreads; i++)
	{	
		if(0 != pthread_create( &threads[i], NULL, Update_ParamsPerThread, (void*)(_gameboard->m_eachThread + i ) ) )
		{
			return;
		}
	}

	for(i = 0; i < numOfThreads ; ++i)
	{
		pthread_join( threads[i], NULL );
	}
	return;
}


/*Updating the next generation by the current generation parameters*/
void ChackAndUpdate(CalcForOne_Thread* _eachThread)
{
	int x, y;
	
	int startCol = _eachThread->m_startColoumn;
	int startRow = _eachThread->m_startRow;
	int endColum = _eachThread->m_endColoumn;
	int endRow =   _eachThread->m_endRow;	
	int beAlive;
	
	for(y = startCol; y <= endColum; ++y)
	{
		for(x = startRow; x <= endRow; ++x)
		{	
			beAlive = _eachThread->m_game->m_ruleFunc( _eachThread->m_boardGame_ForLimit, x, y,IsAlive);
			
			if(1 == beAlive)
			{
				Update_Value( _eachThread->m_boardGame_ForLimit, x, y, 1 );
			}
			
			else if(0 == beAlive)
			{
				Update_Value( _eachThread->m_boardGame_ForLimit, x, y, 0 );
			}
			
		}
	}
	return;
}

void* Update_ParamsPerThread(void* _eachThread)
{
	int i = 0;
	char exit;
	
	int generation =  ( (CalcForOne_Thread*) _eachThread)->m_maxGen;
	CalcForOne_Thread* eachThread = (CalcForOne_Thread*)_eachThread;
	
	for(i = 0; i < generation; ++i)
	{
		
		ChackAndUpdate( eachThread );
		BarrierWait( eachThread->m_barrier);
	}
	
	return NULL;
}

/*Only the last thread will do this function*/
int SwapAndPrintGeneration(void* _gameOfLife)
{
	GameOfLife* l_gameOfLife = ( GameOfLife* )_gameOfLife;
	char buff[1024];
	
	sprintf(buff,"Natali.%04d.ppm", l_gameOfLife->m_numOfGen);
	
	++(l_gameOfLife->m_numOfGen);
	
	SwitchTables( l_gameOfLife->boardGame );
	PrintCurrent_boardGame( l_gameOfLife->boardGame );
	Board_Write_To_PPM( l_gameOfLife->boardGame, buff);
	
	usleep(130000);
	
	return 0;
}

/*Only the last thread will do this function*/
int SwapAndPrint(void* _gameOfLife)
{
	GameOfLife* l_gameOfLife = ( GameOfLife* )_gameOfLife;
	char buff[1024];
	
	sprintf(buff,"Natali.%04d.ppm", l_gameOfLife->m_numOfGen);
	
	++(l_gameOfLife->m_numOfGen);
	
	SwitchTables( l_gameOfLife->boardGame );
	PrintCurrent_boardGame( l_gameOfLife->boardGame );
	Board_Write_To_PPM( l_gameOfLife->boardGame, buff );
	
	usleep(130000);
	
	if(1 == IsEqualeTables( l_gameOfLife->boardGame ) )
	{
		exit(1);
	}
	
	return 0;
}

