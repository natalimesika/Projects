#ifndef __INIT_BOARD_H__
#define __INIT_BOARD_H__

#include "GameBoard.h"


/**
 * @brief Option to boot the board randomly
 * @param[in] _gameBoard: the board game
 * @return non
 */
void InitRandomNum(GameBoard* _gameBoard);


/**
 * @brief Option to boot the board from file
 * @param[in] _gameBoard: the board game
 * @return non
 */
void Init_Board_from_file(GameBoard* _gameBoard, const char* _fileName );


/**
 * @brief Option to boot in line
 * @param[in] _gameBoard: the board game
 * @return non
 */
void Init(GameBoard* _gameBoard);
#endif /* __INIT_BOARD_H__ */

