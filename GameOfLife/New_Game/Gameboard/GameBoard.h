#ifndef __GAME_BOARD_H__
#define __GAME_BOARD_H__

#include <stdlib.h>

/**********************************
	Game_board	  


	Use struct: GameBoard		  

	Create by: Natali mesika		  
*********************************/

typedef struct GameBoard GameBoard; 


/** 
 * @brief Creating a board game and initilize him.
 * @param[in] _rows : The number of rows 
 * @param[in] _ncolumns : The number of columns
 * @param[in] _numOfThreads : The number of threads that will sync 
 * @retvals : pointer to the init board.		
 */ 
GameBoard* CreateGameBoard(size_t _rows, size_t _columns, size_t _numOfThreads, const char* _filename);


/** 
 * @brief Checks whether the coordinates there and live in the present generation
 * @param[in] _currentBoard : The boardGame 
 * @param[in] _r : The specific row
 * @param[in] _c : The specific column
 * @retvals : 1 if the coordinates exist .
 *			: 0 if the coordinates not exist
 */ 
void Update_Value(GameBoard* _currentBoard, size_t _r, size_t _c ,int _statusForNexGan);


/** 
 * @brief check the number of rows in the board
 * @param[in] _currentBoard : The boardGame 
 * @retvals : the number of rows
 */ 
int IsAlive(GameBoard* _currentBoard, size_t _r, size_t _c);

/** 
 * @brief check the number of columns in the board
 * @param[in] _currentBoard : The boardGame 
 * @retvals : the number of columns
 */ 
int NumOfRows( GameBoard* _board );


/** 
 * @brief Replace the board next generation of the current generation
 * @param[in] _currentBoard : The boardGame 
 * @retvals :non
 */ 
int NumOfCol( GameBoard* _board );

/** 
 * @brief Replace the board next generation of the current generation
 * @param[in] _currentBoard : The boardGame 
 * @retvals :non
 */ 
void SwitchTables(GameBoard* _gameBoard);


/** 
 * @brief Looking for a specific spot on the board of the latest generation by rows and columns
 * @param[in] _currentBoard : The boardGame 
 * @param[in] _x : The specific row
 * @param[in] _y : The specific column
 * @retvals :non
 */ 
int Search_Point(GameBoard* _gameBoard, int _x, int _y);


/** 
 * @brief Creates coordinates and puts it to the board
 * @param[in] _currentBoard : The boardGame 
 * @param[in] _x : The specific row
 * @param[in] _y : The specific column
 * @retvals :non
 */ 
void InsertCoordinate(int _x, int _y,  GameBoard* _gameBoard );

/** 
 * @brief Comparison function - Checking whether coordinates is worth a different coordinates
 * @param[in] _currentBoard : The boardGame 
 * @retvals : 1 if the coordinates equal .
 *			: 0 if the coordinates not equal
 */
int IsEqualeTables(GameBoard* _gameBoard);


/** 
 * @brief Destroy the Board
 * @param[in] _currentBoard : The boardGame 
 * @retvals :non
 */ 
void DestroyBoard( GameBoard* _board );




#endif /* __GAME_BOARD_H__ */

