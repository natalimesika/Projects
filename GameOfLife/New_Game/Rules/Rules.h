#ifndef __RULES_H__
#define __RULES_H__

#include <stddef.h>
#include "GameBoard.h"

typedef int (*IsAliveprot)(GameBoard* _currentBoard, size_t _r, size_t _c);

/** 
 * @brief Checking the status of neighbors and accordingly determines the fate of the next generation cell.
 * @param[in] _boardGame : The board game
 * @param[in] _r : The number of rows 
 * @param[in] _c : The number of columns
 * @retvals : pointer to the init board.		
 */ 
int Destiny_decider( GameBoard* boardGame, size_t _r, size_t _c ,IsAliveprot _isalivfunc);


/** 
 * @brief Checking the status of neighbors and accordingly determines the fate of the next generation cell.
 * there is more chance to live because you need you should have a 	better neighbors to die
 * @param[in] _boardGame : The board game
 * @param[in] _r : The number of rows 
 * @param[in] _c : The number of columns
 * @retvals : pointer to the init board.		
 */ 
int Destiny_decider_More_chance_To_Live( GameBoard* boardGame, size_t _r, size_t _c ,IsAliveprot _isalivfunc);


/** 
 * @brief Checking the status of neighbors and accordingly determines the fate of the next generation cell.
 * there is less chance to live because you need you should have a less neighbors to die
 * @param[in] _boardGame : The board game
 * @param[in] _r : The number of rows 
 * @param[in] _c : The number of columns
 * @retvals : pointer to the init board.		
 */
int Destiny_decider_Less_chance_To_Live( GameBoard* boardGame, size_t _r, size_t _c ,IsAliveprot _isalivfunc);

#endif /* __RULES_H__ */

