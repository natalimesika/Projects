#include "ADT_Berrier.h"

#include <pthread.h>		/*For pthreads*/
#include <stdlib.h>			/*For malloc*/
#include <errno.h>
#include <stdio.h>



struct Barrier
{
	pthread_mutex_t     m_mutex;              /* Control access to barrier */
	pthread_cond_t      m_cv;                 /* wait for barrier */
	unsigned int m_numThreads;				  /* how many threads can enter in 1 cycle*/			
	unsigned int m_counter;			  		  /* current number of threads */
	unsigned int m_cycle; 				      /* set*/
	void* m_context;
	ThelastThread m_thelastThread;									  
};


Barrier* BarrierInit( unsigned int _count, ThelastThread _thelastThread, void* _context)
{
	Barrier* barrier;
	int status;
	
	barrier = (Barrier*)malloc( sizeof( Barrier ) );
	if(NULL == barrier )
	{
		return NULL;
	}	
	
	status = pthread_mutex_init(&barrier->m_mutex, NULL);
	if(0 != status)
	{
		free(barrier);
		
		return NULL;
	}

	if(pthread_cond_init(&barrier->m_cv, NULL) < 0)
	{
		pthread_mutex_destroy (&barrier->m_mutex);
		free(barrier);
		
		return NULL;
	}
	
	barrier->m_numThreads = _count;
	barrier->m_counter = 0;
	barrier->m_cycle = 0;
	barrier->m_thelastThread = _thelastThread;/*XXX*/
	barrier->m_context  = _context;
	
 	return barrier;
}


BERRErr BarrierWait(Barrier* _barrier)
{
	int cycle;
	
	if(NULL == _barrier)
	{
		return BERR_UNINITILIZE;
	}
	
	if( pthread_mutex_lock( &_barrier->m_mutex ) < 0)
	{
		return BERR_MUTEX_ERR;
	}
	
    cycle = _barrier->m_cycle;   
	++_barrier->m_counter;
	if ( _barrier->m_numThreads == _barrier->m_counter)
	{
		/*printf("Thread Mashiah: %d, cycle: %d\n",_barrier->m_counter, _barrier->m_cycle);	*/
		/*change the "set" */
        ++_barrier->m_cycle;
        
       	_barrier->m_counter = 0;
       	
		_barrier->m_thelastThread(_barrier->m_context);
      
       	if( 0 != pthread_cond_broadcast(&_barrier->m_cv) )
       	{
			return BERR_COND_ERR;       	
       	}

       	if( 0 != pthread_mutex_unlock( &(_barrier->m_mutex) ) ) 
		{
			return BERR_MUTEX_ERR;
		} 
    }
    /*if this is not the last thread*/
    else 
    {	
    	/*That means this set of threads hasn't changed.*/
    	while(cycle == _barrier->m_cycle)
    	{
    		/*printf("cycle wait: %d\n", _barrier->m_cycle);*/
			if( 0 != pthread_cond_wait(&_barrier->m_cv, &_barrier->m_mutex) )
			{
				return BERR_COND_ERR; 	
			}
    	}
    
		if(0 != pthread_mutex_unlock( &(_barrier->m_mutex) ) ) 
		{
			return BERR_MUTEX_ERR;
		} 
   		return BERR_REPRESENT_LAST_THREADS;
    }
	
    return BERR_OK;
}


void barrier_destroy(Barrier* _barrier)
{
    if(NULL == _barrier)
    {
    	return;
    }
	
    pthread_mutex_destroy(& _barrier->m_mutex);
	pthread_cond_destroy(& _barrier->m_cv);   

	free(_barrier);   
}


