#ifndef __BARRIER_H__
#define __BARRIER_H__


typedef enum 
{
	BERR_OK,
	BERR_FAIL,
	BERR_UNINITILIZE,
	BERR_MUTEX_ERR,
	BERR_COND_ERR,
	BERR_REPRESENT_LAST_THREADS 

}BERRErr;

 

typedef struct Barrier Barrier;

typedef int (*ThelastThread)( void* _context);


/** 
 * @brief creates a new barrier. 
 * @params[in] _thelastThread : function that the last thread of each set will execute.
 * @params[in] _context : for the user
 * @params[in] _count : indicates the number of threads that can enter in one cycle (set).
 * @retvals : pointer to the init barrier.		
 * @retvals : NULL on fail.		
 */ 
Barrier* BarrierInit( unsigned int _count, ThelastThread _thelastThread, void* _context);

/** 
 * @brief Waiting a certain amount of threads to wait at the berrier, and dispatche all the threads that in the set tougether. 
 * @params[in] _barrier : init berrier.
 * @retvals : BERR_MUTEX_ERR : fail on mutex 
 * @retvals : BERR_COND_ERR : fail on condition
 * @retvals : BERR_UNINITILIZE Barrier not initilize
 * @retvals : BERR_OK : on succsses
 */ 

BERRErr BarrierWait(Barrier* _barrier);

/** 
 * @brief destroy the barrier. 
 * @params[in] _barrier :berrier to destroy.
 * @retvals : non.				
 */ 
void barrier_destroy(Barrier* _barrier);




#endif
