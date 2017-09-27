#ifndef __GAME_OF_LIFE_H__
#define __GAME_OF_LIFE_H__

#include <stddef.h>


typedef struct GameOfLife GameOfLife; 

/** 
 * @brief Create game : Game Of life.
 * @param[in] _rows : The number of rows 
 * @param[in] _ncolumns : The number of columns
 * @param[in] _numOfThreads : The number of threads that will sync 
 * @param[in] _numOfGeneration : The number of cycles that the game run
 * @param[in] _stopIfEqual :Parameter that represents whether the user chose to stop when you have identical boards or not.
 * opetion: 1 : the game stoped if the cells will stopes moving
 *		    0 : the game stoped by the number of generations
 * default : If the user presses the number didn't match the optziotth the game stops when you have identical boards.
 * @retvals : pointer to initilize gamboard with the params. NULL on fail.		
 */ 
GameOfLife* CreateGame(size_t _rows, size_t _ncolumns, size_t _numOfThreads, size_t _numOfGeneration ,const char* _filename, size_t _stopIfEqual);


/**
 * @brief The game begins. The Board is divided by the number of threads who choose the user and any thread will update his zone.
 * @param[in] _gameOfLife : new game
 * @return non
 */
void Run_game(GameOfLife* _gameOfLife); 


/**
 * @brief Destroy the all game.
 * @param[in] this function will be open if the game stoped 
 * @return non
 */
void Destroy(GameOfLife* _gameOfLife); 



/**
 * @brief print ans swap board, only the last thread will carry out this function
 * @brief the game will stop only on the last ganaration
 * @param[in] _gameOfLife: pointer to game of life
 * @return 0
 */
int SwapAndPrintGeneration(void* _gameOfLife);

/**
 * @brief print ans swap board, only the last thread will carry out this function
 * @brief the game will stop only on the last ganaration
 * @param[in] _gameOfLife: pointer to game of life
 * @return 0
 */
int SwapAndPrint(void* _gameBoard);


void Load_Rule( GameOfLife* _gameOfLife, size_t _selection );

#endif /* __GAME_OF_LIFE_H__ */
