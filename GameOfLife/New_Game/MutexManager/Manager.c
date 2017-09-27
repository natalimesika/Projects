#include "Manager.h"

#include <pthread.h>
#include <stdlib.h>
#include <errno.h>

#define NUM_TO_TRIES 10
#define NUM_THREADS 1000
#define MAGIC 773634
#define NO_KEY 0
#define UNLOCK 0

static MUTEX_RES InitMutex(pthread_mutex_t* _mutexToInit);

typedef struct MutexDetails MutexDetails;


struct MutexManager
{
	pthread_mutex_t m_chiefMutex;
	MutexDetails* m_mutexData;
	size_t m_numOfThreads;
	int m_magicNumber;
};

struct MutexDetails
{
	pthread_mutex_t m_lock;
	int m_indexKey;
	int m_isLock; 							/*Zero for lock*/
	int m_countEnters;
};

/********/
/*Static*/
/********/
static MUTEX_RES InitMutex(pthread_mutex_t* _mutexToInit);
static MUTEX_RES OpenTheChiefMutex( MutexManager* _mutexMan );
static MUTEX_RES LockTheChiefMutex( MutexManager* _mutexMan );



/**********************/
/*Create Mutex manager*/
/**********************/
MutexManager* CreateManager(size_t _numOfThreads)
{
	size_t i;
	size_t j;
	MUTEX_RES res;
	MutexManager* newMutexman;
	
	if(_numOfThreads < 1)
	{
		return NULL;	
	}
	
	newMutexman = (MutexManager*)malloc( sizeof(MutexManager) );
	if(NULL == newMutexman)
	{
		return NULL;
	}
	
	newMutexman->m_mutexData = malloc(_numOfThreads * sizeof( MutexDetails ) );
	if(NULL == 	newMutexman->m_mutexData )
	{
		free(newMutexman);
		
		return NULL;
	}
	
	/*Init the chief*/
	res = InitMutex( &newMutexman->m_chiefMutex );
	if(res != MUTEX_MAN_OK)
	{
		free(newMutexman->m_mutexData);
		free(newMutexman);
		
		return NULL;
	}
	
	for(i = 0; i < _numOfThreads; ++i)
	{	
		/*Init the array of mutexs*/
		res = InitMutex( &(newMutexman->m_mutexData[i] ).m_lock);
		if(res != MUTEX_MAN_OK)
		{
			for(j = i; j > 0; --j)
			{
				pthread_mutex_destroy( &(newMutexman->m_mutexData[j] ).m_lock);
			}
			
			free(newMutexman->m_mutexData);
			free(newMutexman);
			
			return NULL;
		}

		newMutexman->m_mutexData[i].m_countEnters = 0;
		newMutexman->m_mutexData[i].m_indexKey = NO_KEY;	
		newMutexman->m_mutexData[i].m_isLock = UNLOCK;
	}

	newMutexman->m_numOfThreads = _numOfThreads;
	newMutexman->m_magicNumber = MAGIC;
	
	return newMutexman;
}

/**********************/
/*Destroy_manager	  */
/**********************/
void Destroy_manager(MutexManager* _mutexMan)
{
	int i;
	
	if(NULL == _mutexMan)
	{
		return;
	}
	
	for(i = 0; i < _mutexMan->m_numOfThreads; ++i)
	{
		if(0 != pthread_mutex_destroy( &( _mutexMan->m_mutexData[i].m_lock) )  )
		{
			return;
		}
	}
	pthread_mutex_destroy(&_mutexMan->m_chiefMutex);
	
	free(_mutexMan->m_mutexData);
	free(_mutexMan);

}

/******************************************/
/*				LockTheBucket			  */
/******************************************/

MUTEX_RES LockTheBucket(MutexManager* _mutexMan, size_t _indexBucket)
{
	int i;
	MUTEX_RES res;
	
	if(NULL == _mutexMan || _indexBucket < 0 )
	{
		return MUTEX_MAN_VALID_ERR;
	}
	res = LockTheChiefMutex( _mutexMan );
	{
		if(MUTEX_MAN_OK != res)
		{
			return MUTEX_MAN_MAIN_MUTEX_ERR;
		}
	}	

	for(i = 0; i < _mutexMan->m_numOfThreads; ++i)
	{
		/*Its lock*/
		if( _mutexMan->m_mutexData[i].m_indexKey == _indexBucket)
		{
			++( _mutexMan->m_mutexData[i].m_countEnters );
			res = OpenTheChiefMutex( _mutexMan );
			if(MUTEX_MAN_OK != res)
			{
				return MUTEX_MAN_MAIN_MUTEX_ERR;
			}

			pthread_mutex_lock( &(_mutexMan->m_mutexData[i].m_lock ) );					/*Lock the current mutex*/
			
			return MUTEX_MAN_OK;			
		}
	}
	/*If the index key not found: */
	for(i = 0; i < _mutexMan->m_numOfThreads; ++i)
	{
		if( _mutexMan->m_mutexData[i].m_indexKey ==  NO_KEY )
		{
			++( _mutexMan->m_mutexData[i].m_countEnters );

			_mutexMan->m_mutexData[i].m_indexKey = _indexBucket;		
			
			res = OpenTheChiefMutex( _mutexMan );
			if(MUTEX_MAN_OK != res)
			{
				return MUTEX_MAN_MAIN_MUTEX_ERR;
			}

			pthread_mutex_lock( &( _mutexMan->m_mutexData[i].m_lock) );
			
			return MUTEX_MAN_OK;
		}
	}
	return MUTEX_MAN_OK;
}

/******************************************/
/*				FreeBucket  			  */
/******************************************/
MUTEX_RES FreeBucket(MutexManager* _mutexMan, size_t _indexBucket)
{
	
	MUTEX_RES res;
	int i;
	
	if(NULL == _mutexMan || _indexBucket < 0 )
	{
		return MUTEX_MAN_VALID_ERR;
	}
	
	res = LockTheChiefMutex( _mutexMan );
	{
		if(MUTEX_MAN_OK != res)
		{
			return MUTEX_MAN_MAIN_MUTEX_ERR;
		}
	}	
	for (i = 0; i < _mutexMan->m_numOfThreads; ++i)
	{
		if(_mutexMan->m_mutexData[i].m_indexKey == _indexBucket )
		{
	
			--( (_mutexMan->m_mutexData[i].m_countEnters) );
			if( (_mutexMan->m_mutexData[i].m_countEnters == 0 ) )
			{
				_mutexMan->m_mutexData[i].m_indexKey = 0;
			}

			res = OpenTheChiefMutex( _mutexMan );
			if(MUTEX_MAN_OK != res)
			{
				return MUTEX_MAN_MAIN_MUTEX_ERR;
			}
			
			pthread_mutex_unlock( &(_mutexMan->m_mutexData[i].m_lock) );
			
			return MUTEX_MAN_OK;
		}
	}
	return MUTEX_MAN_OK;
}

/******************************************************************************************************************/
/*											Static Function														  */
/******************************************************************************************************************/
/*try to lock the mutex 10 times*/
static MUTEX_RES InitMutex(pthread_mutex_t* _mutexToInit)
{
	int i;
	 
	for(i = 0; i < NUM_TO_TRIES; ++i)
	{
		if( 0 == pthread_mutex_init( _mutexToInit, NULL) )
		{
			return MUTEX_MAN_OK;
		}
		
		else if( EAGAIN == pthread_mutex_init( _mutexToInit, NULL) )
		{
			++i;
		}
		
		else
		{
			return MUTEX_MAN_MAIN_MUTEX_ERR;
		}
	}
	
	return MUTEX_MAN_MAIN_MUTEX_ERR;
}


/**********************/
/*Lock the Chief*/
/**********************/
static MUTEX_RES LockTheChiefMutex( MutexManager* _mutexMan )
{
	if(NULL == _mutexMan)
	{
		return MUTEX_MAN_VALID_ERR;
	}

	if (0 != pthread_mutex_lock(& _mutexMan->m_chiefMutex ) )
	{
		return MUTEX_MAN_MAIN_MUTEX_ERR;
	}

	return MUTEX_MAN_OK;
}


/**********************/
/*Unlock the Chief*/
/**********************/
static MUTEX_RES OpenTheChiefMutex( MutexManager* _mutexMan )
{
	if(NULL == _mutexMan)
	{
		return MUTEX_MAN_VALID_ERR;
	}

	if (0 != pthread_mutex_unlock(& _mutexMan->m_chiefMutex ) )
	{
		return MUTEX_MAN_MAIN_MUTEX_ERR;
	}

	return MUTEX_MAN_OK;
}

