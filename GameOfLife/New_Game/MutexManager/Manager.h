#ifndef __MANAGER_H__
#define __MANAGER_H__

#include <stddef.h>
#include <pthread.h>

typedef struct MutexManager MutexManager;

typedef enum
{
	MUTEX_MAN_OK, /*=0*/
	MUTEX_MAN_FAIL, 
	MUTEX_MAN_MAIN_MUTEX_ERR, 
	MUTEX_MAN_VALID_ERR

}MUTEX_RES;

/**
 * @brief Create mutex managar. init the params for ADTs served.
 * @param[in] _numOfThreads : The number of threads that will sync 
 * @return pointer to the mutex managar
 */
MutexManager* CreateManager(size_t _numOfThreads);


/**
 * @brief Lock the bucket for one thread.
 * @param[in] _mutexMan : pointer to the mutex managar
 * @param[in] _indexBucket : the bucket that the thread use now
 * @return pointer to one mutex that locked now
 */
 
 
MUTEX_RES LockTheBucket(MutexManager* _mutexMan, size_t _indexBucket);

/**
 * @brief Free the bucket for one thread.
 * @param[in] _mutexMan : pointer to the mutex managar
 * @param[in] _indexBucket : the bucket that the thread use now
 * @return MUTEX_MAN_OK on succsses
 * @return MUTEX_MAN_OK on succsses
 
 */
MUTEX_RES FreeBucket(MutexManager* _mutexMan, size_t _indexBucket);


/**
 * @brief Destroy the mutex managar.
 * @param[in] _mutexMan : pointer to the mutex managar that need to be destroy; 
 * @return non
 */
void Destroy_manager(MutexManager* _mutexMan);


#endif /* __MANAGER_H__ */

