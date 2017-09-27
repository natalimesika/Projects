#ifndef __PLAY_IN_GAME_OF_LIFE_H__
#define __PLAY_IN_GAME_OF_LIFE_H__

#include "Game_of_life.h"

/**********************************
	Game of life	:User Interface   

	Use struct: GameOfLife		  

	Create by: Natali mesika		  
*********************************/

/**
 * @brief Create game : Game Of life.
 * The "game" is a zero-player game, meaning that its evolution is determined by its initial state,
 * requiring no further input. One interacts with the Game of Life by creating an initial configuration and observing how it evolves,
 * or, for advanced "players", by creating patterns with particular properties.
 * @param[in] _nRows : The number of rows 
 * @param[in] _ncolumns : The number of columns
 * @param[in] _numOfThreads : The number of threads that will sync 
 * @param[in] _numOfGeneration : The number of cycles that the game run
 * @param[in] _stopIfEqual : opetion: 1 : the game stoped if the cells will stopes moving
 									  0 : the game stoped by the number of generations
 * @return pointer to new game
 */

GameOfLife* CreateNewGame(size_t _nRows, size_t _ncolumns, size_t _numOfThreads, size_t _numOfGeneration, const char* _filename, size_t _stopIfEqual);

/**
 * @brief the game start.
 * @param[in] _newGame : new game
 * @return non
 */

void RunNewGame(GameOfLife* _newGame);

#endif /* __PLAY_IN_GAME_OF_LIFE_H__ */

